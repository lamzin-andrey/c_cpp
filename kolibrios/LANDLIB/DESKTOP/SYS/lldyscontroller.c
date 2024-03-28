
//#include <clayer/boxlib.h>
#include "landinput.h"
#include "plldsyscontroller.c"

void onKeyPress(char* id, uint32_t code);
void onLeftMouseDown(char* id, UINT mX, UINT mY, UINT btnId);
void onRightMouseDown(char* id, UINT mX, UINT mY, UINT btnId);
void onClick(char* id, UINT mX, UINT mY, UINT btnId);
void onRightClick(char* id, UINT mX, UINT mY, UINT btnId);
void onMouseMove(char* id, UINT mX, UINT mY, UINT btnId);

void lld_sys_render(edit_box* ed, check_box output_off, char* ed_buff, char* title) {

	edit_box_draw(ed);
    check_box_draw2(&output_off);
    if (!output_off.flags) {
        _ksys_draw_text(ed_buff, 10, 90, strlen(ed_buff), BLACK | TEXT_SIZE);
        //_ksys_set_window_title(title);
    }

    for (long i = 0; i <= LLDO_ITERATOR; i++) {
      char* type = LLDO_TYPES[i];
      if (0 == strcmp("itext", type)) {
        edit_box_draw(&LLDO_INP_TEXT[i].ebox);
      }
      if (0 == strcmp("icheckbox", type)) {
        check_box_draw2(&LLDO_CHB[i].checkbox);
      }
      if (0 == strcmp("img", type)) {
        Img img = LLDO_IMG[i];
        if (1 == img.tabSupport) {
        	_ksys_draw_bar(img.x, img.y, img.w + 2, img.h + 2, LLDI_ALPHA_COLOR);
        	landDrawImageWH(img.src, img.x + 1, img.y + 1, img.w, img.h);
        } else {
        	landDrawImageWH(img.src, img.x, img.y, img.w, img.h);
        }

      }
      if (0 == strcmp("text", type)) {
        StaticText t = LLDO_TEXT[i];
        landDrawStaticText(t);
      }
      if (0 == strcmp("btn", type)) {
        LLDButton b = LLDO_BTN[i];
        landDrawButton(b);
      }
    }

}


void lldSysOnMouseEvent(UINT pressed_button)
{
	ksys_pos_t mouse_pos;
	uint32_t mouse_button;
	mouse_pos = _ksys_get_mouse_pos(KSYS_MOUSE_WINDOW_POS); // window relative
	mouse_button = _ksys_get_mouse_eventstate();


	UINT mX = (UINT)mouse_pos.x;
	UINT mY = (UINT)mouse_pos.y;
	long btnId = -1;
	char mouseBtn = (char)mouse_button;
	char* id = getIdByMousePos(mX, mY, &btnId);


	if (mouse_button & (1 << 24)) // double click
	{

	}

	for (long i = 0; i <= LLDO_ITERATOR; i++) {
      char* type = LLDO_TYPES[i];

      if (0 == strcmp("itext", type)) {
        edit_box_mouse(&LLDO_INP_TEXT[i].ebox);
      }
      if (0 == strcmp("icheckbox", type)) {
        check_box_mouse2(&LLDO_CHB[i].checkbox);
      }
    }

    if (1 == mouseBtn) {
    	onLeftMouseDown(id, mX, mY, pressed_button);
    	prevMouseBtn = 1;
    }

    if (2 == mouseBtn) {
    	onRightMouseDown(id, mX, mY, pressed_button);
    	prevMouseBtn = 2;
    }

    if (0 == mouseBtn) {
    	if (1 == prevMouseBtn) {
    		onClick(id, mX, mY, pressed_button);
    	}
    	if (2 == prevMouseBtn) {
    		onRightClick(id, mX, mY, pressed_button);
    	}
    	prevMouseBtn = 0;
    }
    if (prevMX != mX || prevMY != mY) {
    	onMouseMove(id, mX, mY, btnId);
    	prevMX = mX;
    	prevMY = mY;
    }
}


void lldSysOnKeyPressEvent(ksys_oskey_t ch) {

  for (long i = 0; i <= LLDO_ITERATOR; i++) {
      char* type = LLDO_TYPES[i];

      if (0 == strcmp("itext", type)) {
        edit_box_key_safe(&LLDO_INP_TEXT[i].ebox, ch);
        // TODO call appcontroller with id
        onKeyPress(LLDO_INP_TEXT[i].id, ch);
      }
  }
}