#ifndef LANDLIB_IMAGE_HEADER
#define LANDLIB_IMAGE_HEADER

#include <clayer/libimg.h>
#include "../../dummyphpc/dphpc.h"

#define LLD_IMAGES_SZ  4096

char*        LLDI_SRC[LLD_IMAGES_SZ];
Image        LLDI_IMAGES[LLD_IMAGES_SZ];
long         LLDI_ITERATOR = -1;
UINT         LLDI_ALPHA_COLOR = 0xD2D0C2;

char*       logFile = "logImg.txt";

// Здесь только методы, загружающие и отрислвывающие изображения. Поэтому у них префикс Draw
// Связь этого со структурами для рендеринга через LLDO_TYPES там же, где и весь остальной GUI

// public
/**
 * Автоматически масштабирует высоту по ширине.
*/
void landDrawImageW(char* src, UINT x, UINT y, UINT w);
void landDrawImage(char* src, UINT x, UINT y, UINT w); // alias for void landDrawImageW
void setAlphaColor(UINT alphaColor);
/**
 * Автоматически масштабирует ширину по высоте.
*/
//void landDrawImageH(char* src, UINT x, UINT y, UINT h);
/**
 * Масштабирует и высоту и шиирину
*/
void landDrawImageWH(char* src, UINT x, UINT y, UINT w, UINT h);
/**
 * Масштабирует и высоту по ширине, заданной в процентах.
*/
//void landDrawImageWP(char* src, UINT x, UINT y, char w);

/**
 * Масштабирует ширину по высоте, заданной в процентах.
*/
//void landDrawImageHP(char* src, UINT x, UINT y, char h);

/**
 * Масштабирует и высоту и шиирину переданые в процентах.
*/
//void landDrawImageWHP(char* src, UINT x, UINT y, char w, char h);

/**
 * Просто выводит как есть.
*/
void landDrawImageN(char* src, UINT x, UINT y);


// private
void* landImgLoadPngFromFile(char* file, uint32_t* read_sz);
Image* landImgPreparePngData(void* fileData, uint32_t* imgSize);
Image* landImgFind(char* src);


#endif /* LANDLIB_IMAGE_HEADER */