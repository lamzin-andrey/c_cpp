
#include "landinput.h"


char* fillEmpStr(char* textContent, int length) {
   char* r = NULL;
   r = malloc(length);
   for (int i = 0; i < length; i++) {
     r[i] = '\0';
   }

   textContent = r;

   return textContent;
}


// image item

Img* lldImg(char* id, char* src, UINT x, UINT y, UINT w) {
	return lldImgC(id, src, x, y, w, LLDI_DEFAULT_BG_COLOR);
}

Img* lldImgC(char* id, char* src, UINT x, UINT y, UINT w, UINT alphaColor) {
  LLDO_ITERATOR++;
  if (LLDO_ITERATOR >= DISPLAY_OBJ_SZ) {
    return NULL;
  }

  /*char* textContent = malloc(DISPLAY_OBJ_SZ);
  strcpy(textContent, src);
  for (int i = strlen(label); i < DISPLAY_OBJ_SZ; i++) {
    textContent[i] = '\0';
  } */


  //UINT sysTextColor = 0x90000000 | sys_color_table.work_button_text; // TODO apply!
  LLDO_IMG[LLDO_ITERATOR].id = (char*)id;
  LLDO_IMG[LLDO_ITERATOR].x = x;
  LLDO_IMG[LLDO_ITERATOR].y = y;
  LLDO_IMG[LLDO_ITERATOR].w = w;
  LLDO_IMG[LLDO_ITERATOR].src = (char*)src;
  setAlphaColor(alphaColor);
  Image* img = landImgFind(src);

  LLDO_IMG[LLDO_ITERATOR].tabSupport = 0;
  if (TabIndexDefaultMode > 0) {
    LLDO_TAB_INDEX++;
  	LLDO_IMG[LLDO_ITERATOR].tabIndex = LLDO_TAB_INDEX;
  	LLDO_IMG[LLDO_ITERATOR].tabSupport = 1;
  }


  if (img) {
  	double k = (double)w; // ‚®«è¥¡­ ï áâà®ª , ¡¥§ ­¥ ­¥ à ¡®â ¥â.
  	double scale = (double)w / (double)(UINT)img->Width;
  	double fH = scale * img->Height;
  	UINT h = (UINT)fH;

  	LLDO_IMG[LLDO_ITERATOR].h = h;
  	LLDO_IMG[LLDO_ITERATOR].img = img;
  } else {
  	LLDO_IMG[LLDO_ITERATOR].w = 0;
  	LLDO_IMG[LLDO_ITERATOR].h = 0;
  }
  LLDO_IMG[LLDO_ITERATOR].alphaColor = alphaColor;
  LLDO_TYPES[LLDO_ITERATOR] = "img";

  return &LLDO_IMG[LLDO_ITERATOR];
}


// input checkbox
void lldICheckboxC(char* id, UINT x, UINT y, char* label, UINT  bgColor, UINT color) {

  LLDO_ITERATOR++;
  if (LLDO_ITERATOR >= DISPLAY_OBJ_SZ) {
    return;
  }



  char* textContent = malloc(DISPLAY_OBJ_SZ); // TODO DISPLAY_OBJ_SZ
  strcpy(textContent, label);
  for (int i = strlen(label); i < DISPLAY_OBJ_SZ; i++) {
    textContent[i] = '\0';
  }



  //check_box cb = { X_W(x, 15), Y_H(y, 15), 30, 0xFFFFFF, 0x0000FF, 0x000000 | TEXT_SIZE, textContent, 0 };

  UINT sysTextColor = 0x90000000 | sys_color_table.work_button_text; // TODO apply!
  LLDO_CHB[LLDO_ITERATOR].id = (char*)id;
  LLDO_CHB[LLDO_ITERATOR].x = x;
  LLDO_CHB[LLDO_ITERATOR].y = y;
  LLDO_CHB[LLDO_ITERATOR].h = 13;
  LLDO_CHB[LLDO_ITERATOR].wI = 13;
  LLDO_CHB[LLDO_ITERATOR].state = 0;
  LLDO_CHB[LLDO_ITERATOR].label = textContent;
  LLDO_CHB[LLDO_ITERATOR].marginRight = 10;
  LLDO_CHB[LLDO_ITERATOR].w = 13 + 10 + (8 * strlen(textContent));
  LLDO_TAB_INDEX++;
  LLDO_CHB[LLDO_ITERATOR].tabIndex = LLDO_TAB_INDEX;

  LLDO_TYPES[LLDO_ITERATOR] = "icheckbox";


}

void lldICheckbox(char* id, UINT x, UINT y, char* val) {
  lldICheckboxC(id, x, y, val, 0x000000, 0x000000);
}

// input text
void lldITextS‘(char* id, UINT x, UINT y, UINT w, UINT h, char* val, UINT  bgColor, UINT color) {

  LLDO_ITERATOR++;
  if (LLDO_ITERATOR >= DISPLAY_OBJ_SZ) {
    return;
  }

  char* textContent;
  textContent = malloc(DISPLAY_OBJ_SZ);
  //textContent = fillEmpStr(textContent, 255);
  for (int i = 0; i < DISPLAY_OBJ_SZ; i++) {
  	textContent[i] = '\0';
  }

  // TODO æ¢¥â  ¡à âì ¨§ â¥¬ë.
  //
  LLDO_TYPES[LLDO_ITERATOR] = "itext";


  LLDO_INP_TEXT[LLDO_ITERATOR].id = (char*)id;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.width = w;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.left = x;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.top = y;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.color = bgColor;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.shift_color = color;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.focus_border_color = 0;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.blur_border_color = color;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.text_color = 0x000000 | TEXT_SIZE;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.max = DISPLAY_OBJ_SZ;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.text = textContent;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.mouse_variable = NULL;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.flags = 0/*ed_focus*/;
  LLDO_INP_TEXT[LLDO_ITERATOR].ebox.height = h;
  LLDO_INP_TEXT[LLDO_ITERATOR].text = val;
  LLDO_TAB_INDEX++;
  LLDO_INP_TEXT[LLDO_ITERATOR].tabIndex = LLDO_TAB_INDEX;

  if (strlen(val) > 0) {
  	edit_box_set_text(&LLDO_INP_TEXT[LLDO_ITERATOR].ebox, val);
  }

}



void lldITextS(char* id, UINT x, UINT y, UINT w, UINT h, char* val) {
  //UINT color = 0x90000000 | sys_color_table.work_button_text;
  lldITextS‘(id, x, y, w, h, val, 0xFFFFFF, 0x6a9480);
}


void lldIText(char* id, UINT x, UINT y, char* val) {
  lldITextS(id, x, y, 100, 32, val);
}

StaticText* lldTextPBC(char* id, char* val, UINT x, UINT y, char padding, UINT borderColor, UINT borderWidth, UINT bgColor, UINT color) {
  LLDO_ITERATOR++;
  if (LLDO_ITERATOR >= DISPLAY_OBJ_SZ) {
    return NULL;
  }



  UINT h = 10;
  UINT w = 6 * strlen(val);

  LLDO_TYPES[LLDO_ITERATOR] = "text";

  LLDO_TEXT[LLDO_ITERATOR].id = (char*)id;
  LLDO_TEXT[LLDO_ITERATOR].w = w;
  LLDO_TEXT[LLDO_ITERATOR].x = x;
  LLDO_TEXT[LLDO_ITERATOR].y = y;
  LLDO_TEXT[LLDO_ITERATOR].bgColor = bgColor;
  LLDO_TEXT[LLDO_ITERATOR].color = color;
  LLDO_TEXT[LLDO_ITERATOR].savedColor = color;
  LLDO_TEXT[LLDO_ITERATOR].borderColor = borderColor;
  LLDO_TEXT[LLDO_ITERATOR].borderWidth = borderWidth;
  LLDO_TEXT[LLDO_ITERATOR].padding = padding;
  LLDO_TEXT[LLDO_ITERATOR].text = val;
  LLDO_TEXT[LLDO_ITERATOR].h = h;
  LLDO_TEXT[LLDO_ITERATOR].fontType = FONT_TYPE10;

  if (TabIndexDefaultMode > 2) {
  	LLDO_TAB_INDEX++;
  	LLDO_TEXT[LLDO_ITERATOR].tabIndex = LLDO_TAB_INDEX;
  }

  return &LLDO_TEXT[LLDO_ITERATOR];
}

StaticText* lldTextPB(char* id, char* val, UINT x, UINT y, char padding, UINT borderColor, UINT borderWidth) {
	return lldTextPBC(id, val, x, y, padding, borderColor, borderWidth, LLDI_DEFAULT_BG_COLOR, 0x000000);
}

StaticText* lldTextP(char* id, char* val, UINT x, UINT y, char padding) {
	return lldTextPB(id, val, x, y, padding, 0, 0);
}

StaticText* lldText(char* id, char* val, UINT x, UINT y) {
	return lldTextPB(id, val, x, y, 0, 0, 0);
}

StaticText* lldLabel(char* id, char* val, UINT x, UINT y, UINT bgColor, UINT color) {
	return lldTextPBC(id, val, x, y, 10, 0, 0, bgColor, color);
}

StaticText* lldLabelB(char* id, char* val, UINT x, UINT y, UINT bgColor, UINT color, UINT borderColor, UINT borderWidth) {
	return lldTextPBC(id, val, x, y, 10, borderColor, borderWidth, bgColor, color);
}

LLDButton* lldButtonC(char* id, char* text, UINT x, UINT y, UINT bgColor, UINT color) {
  LLDO_ITERATOR++;
  if (LLDO_ITERATOR >= DISPLAY_OBJ_SZ) {
    return NULL;
  }

  UINT h = 28;
  UINT w = 6 * strlen(text) + 24;

  LLDO_TYPES[LLDO_ITERATOR] = "btn";

  LLDO_BTN[LLDO_ITERATOR].id = (char*)id;
  LLDO_BTN[LLDO_ITERATOR].w = w;
  LLDO_BTN[LLDO_ITERATOR].x = x;
  LLDO_BTN[LLDO_ITERATOR].y = y;
  LLDO_BTN[LLDO_ITERATOR].bgColor = bgColor;
  LLDO_BTN[LLDO_ITERATOR].color = color;
  LLDO_BTN[LLDO_ITERATOR].savedColor = color;
  LLDO_BTN[LLDO_ITERATOR].text = text;
  LLDO_BTN[LLDO_ITERATOR].h = h;
  LLDO_TAB_INDEX++;
  LLDO_BTN[LLDO_ITERATOR].tabIndex = LLDO_TAB_INDEX;
  LLDO_BTN[LLDO_ITERATOR].fontType = FONT_TYPE10;
  LLDO_BTN[LLDO_ITERATOR].intId = LLDO_ITERATOR;

  return &LLDO_BTN[LLDO_ITERATOR];
}

LLDButton* lldButton(char* id, char* text, UINT x, UINT y) {
	return lldButtonC(id, text, x, y, LLDI_DEFAULT_BG_COLOR, 0x000000);
}

LLDButton* lldGreenButton(char* id, char* text, UINT x, UINT y) {
	return lldButtonC(id, text, x, y, 0x00AA00, 0xFFFFFF);
}

LLDButton* lldBlueButton(char* id, char* text, UINT x, UINT y) {
	return lldButtonC(id, text, x, y, 0x0000AA, 0xFFFFFF);
}

LLDButton* lldRedButton(char* id, char* text, UINT x, UINT y) {
	return lldButtonC(id, text, x, y, 0xAA0000, 0xFFFFFF);
}

LLDButton* lldPrimaryButton(char* id, char* text, UINT x, UINT y) {
	return lldButtonC(id, text, x, y, 0x0069D9, 0xFFFFFF);
}

VScroll* lldVScroll(char* id, int x, int h) {  // h = 0 is autosize. h > 0 is vertical size (pixels);
  LLDO_ITERATOR++;
  if (LLDO_ITERATOR >= DISPLAY_OBJ_SZ) {
    return NULL;
  }

  LLDO_TYPES[LLDO_ITERATOR] = "vscroll";

  LLDO_VSCROLL[LLDO_ITERATOR].id = (char*)id;
  LLDO_VSCROLL[LLDO_ITERATOR].x = x;
  LLDO_VSCROLL[LLDO_ITERATOR].h = h;
  LLDO_VSCROLL[LLDO_ITERATOR].hasNormal = 0;
  LLDO_VSCROLL[LLDO_ITERATOR].offsetY = 23;

  scrollbar sc = { LLD_SCROLL_WIDTH, 100 - 26, 100 - 29, 0, 0, 2, 215, LLD_SCROLL_WIDTH, 0, 0xEEEEEE, 0xC3D5FD, 0x555555 };
  LLDO_VSCROLL[LLDO_ITERATOR].sc = sc;

  return &LLDO_VSCROLL[LLDO_ITERATOR];
}
//VScroll*   lldVScrollP(char* id, int x, int h); // h is percent

HScroll*   lldHScroll(char* id, int y, int w) {  // h = 0 is autosize. h > 0 is vertical size (pixels);
  LLDO_ITERATOR++;
  if (LLDO_ITERATOR >= DISPLAY_OBJ_SZ) {
    return NULL;
  }

  LLDO_TYPES[LLDO_ITERATOR] = "hscroll";

  LLDO_HSCROLL[LLDO_ITERATOR].id = (char*)id;
  LLDO_HSCROLL[LLDO_ITERATOR].y = y;
  LLDO_HSCROLL[LLDO_ITERATOR].w = w;
  LLDO_HSCROLL[LLDO_ITERATOR].hasNormal = 0;
  LLDO_HSCROLL[LLDO_ITERATOR].offsetX = 4;

  scrollbar sc = { LLD_SCROLL_WIDTH, 100 - 26, 100 - 29, 0, 0, 2, 215, LLD_SCROLL_WIDTH, 0, 0xEEEEEE, 0xC3D5FD, 0x555555 };
  sc.ysize = LLD_SCROLL_WIDTH;
  LLDO_HSCROLL[LLDO_ITERATOR].sc = sc;

  return &LLDO_HSCROLL[LLDO_ITERATOR];
}