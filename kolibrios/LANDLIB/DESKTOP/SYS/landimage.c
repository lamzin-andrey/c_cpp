#include "landimage.h"

// private
void* landImgLoadPngFromFile(char* file, uint32_t* read_sz) {

	FILE* f = fopen(file, "rb");
    if (!f) {
        //printf("Can't open file: %s\n", file);
        file_put_contentsa(logFile, "Can't open file\n", 8);
        return NULL;
    }
    if (fseek(f, 0, SEEK_END)) {
        //printf("Can't SEEK_END file: %s\n", file);
        file_put_contentsa(logFile, "Can't SEEK_END file\n", 8);
        return NULL;
    }
    int filesize = ftell(f);
    rewind(f);
    void* fdata = malloc(filesize);
    if (!fdata) {
        //printf("No memory for file %s\n", file);
        file_put_contentsa(logFile, "No memory for file\n", 8);
        return NULL;
    }
    *read_sz = fread(fdata, 1, filesize, f);
    if (ferror(f)) {
        //printf("Error reading file %s\n", file);
        file_put_contentsa(logFile, "Error reading file\n", 8);
        return NULL;
    }
    fclose(f);
    return fdata;
}

Image* landImgPreparePngData(void* fileData, uint32_t* imgSize) {
	Image* image = img_decode(fileData, imgSize, 0); // Decode RAW data to Image data

    if (image->Type != IMAGE_BPP32) {
        image = img_convert(image, NULL, IMAGE_BPP32, 0, 0); // Convert image to format BPP32
        if (!image) {
            //printf("Сonvert error!: \n");
            file_put_contentsa(logFile, "Сonvert error!: \n", 8);

            return NULL;
        }
    }

    Image* result = img_create(image->Width, image->Height, IMAGE_BPP32);                  // Create an empty layer
    img_fill_color(result, image->Width, image->Height, LLDI_ALPHA_COLOR/*0xD2D0C2*//*0xEFE9D6*/); // Fill the layer with one color
    img_blend(result, image, 0, 0, 0, 0, image->Width, image->Height);                          // Blending images to display the alpha channel.

    free(image);

    return result;
}

Image* landImgFind(char* src) {
	//file_put_contentsa(logFile, "Call landImgFind\n", 8);
	int i;
	for (i = 0; i <= LLDI_ITERATOR; i++) {
	    if (0 == strcmp(src, LLDI_SRC[i])) {
	    	return &LLDI_IMAGES[i];
	    }
	}

	if (file_exists(src)) {
		uint32_t readSz;
		void* data = landImgLoadPngFromFile(src, &readSz);
		if (!data) {
			return NULL;
		}
		Image* img = landImgPreparePngData(data, &readSz);
		free(data);
		if (!img) {
			return NULL;
		}

		LLDI_ITERATOR++;
		LLDI_SRC[LLDI_ITERATOR] = src;
		LLDI_IMAGES[LLDI_ITERATOR].Checksum = img->Checksum;
		LLDI_IMAGES[LLDI_ITERATOR].Width = img->Width;
		LLDI_IMAGES[LLDI_ITERATOR].Height = img->Height;
		LLDI_IMAGES[LLDI_ITERATOR].Next = img->Next;
		LLDI_IMAGES[LLDI_ITERATOR].Previous = img->Previous;
		LLDI_IMAGES[LLDI_ITERATOR].Type = img->Type;
		LLDI_IMAGES[LLDI_ITERATOR].Data = img->Data;
		LLDI_IMAGES[LLDI_ITERATOR].Palette = img->Palette;
		LLDI_IMAGES[LLDI_ITERATOR].Extended = img->Extended;
		LLDI_IMAGES[LLDI_ITERATOR].Flags = img->Flags;
		LLDI_IMAGES[LLDI_ITERATOR].Delay = img->Delay;

		return &LLDI_IMAGES[LLDI_ITERATOR];
	} else {
		file_put_contentsa(logFile, "Файл не найден вернем NULL: \n", 8);
	}

	return NULL;
}

// public

void setAlphaColor(UINT alphaColor) {
	LLDI_ALPHA_COLOR = alphaColor;
}

/**
 * Автоматически масштабирует высоту по ширине.
*/
void landDrawImage(char* src, UINT x, UINT y, UINT w) {
	landDrawImageW(src, x, y, w);
}
void landDrawImageW(char* src, UINT x, UINT y, UINT w) {
}
void landDrawImageWC(char* src, UINT x, UINT y, UINT w) {
	file_put_contents(logFile, "Call landDrawImageW\n");
	Image* img = landImgFind(src); //если нет в массиве, загружает и сохраняет. Если есть, вернет, что есть.
	if (!img) {
		char* msg = "Not found ";
		msg = addstr(msg, src);
		msg = addstr(msg, "\n");
		file_put_contents(logFile, msg);
	    return;
	}


	double k = (double)w; // Волшебная строка, без не не работает.

	double scale = (double)w / (double)(UINT)img->Width;
	double fH = scale * img->Height;
	UINT h = (UINT)fH;
	img = img_scale(img, 0, 0, img->Width, img->Height, NULL, LIBIMG_SCALE_STRETCH, LIBIMG_INTER_BILINEAR, w, h);
	img_draw(img, x, y, img->Width, img->Height, 0, 0);
}

/**
 * Масштабирует и высоту и шиирину
*/
void landDrawImageWH(char* src, UINT x, UINT y, UINT w, UINT h) {
	file_put_contents(logFile, "Call landDrawImageWH\n");
	Image* img = landImgFind(src); //если нет в массиве, загружает и сохраняет. Если есть, вернет, что есть.
	if (!img) {
	    return;
	}
	img = img_scale(img, 0, 0, img->Width, img->Height, NULL, LIBIMG_SCALE_STRETCH, LIBIMG_INTER_BILINEAR, w, h);
	img_draw(img, x, y, img->Width, img->Height, 0, 0);
}

/**
 * Просто выводит как есть.
*/
void landDrawImageN(char* src, UINT x, UINT y) {
	file_put_contents(logFile, "Call landDrawImageN\n");
	Image* img = landImgFind(src); //если нет в массиве, загружает и сохраняет. Если есть, вернет, что есть.
	if (!img) {
	    return;
	}
	img_draw(img, x, y, img->Width, img->Height, 0, 0);
}




