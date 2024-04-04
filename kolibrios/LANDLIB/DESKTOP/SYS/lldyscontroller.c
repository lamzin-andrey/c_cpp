
//#include <clayer/boxlib.h>
#include "landinput.h"
#include "micron.h"
#include "plldsyscontroller.c"

void onKeyPress(char* id, uint32_t code);
void onLeftMouseDown(char* id, UINT mX, UINT mY, UINT btnId);
void onRightMouseDown(char* id, UINT mX, UINT mY, UINT btnId);
void onClick(char* id, UINT mX, UINT mY, UINT btnId);
void onRightClick(char* id, UINT mX, UINT mY, UINT btnId);
void onMouseMove(char* id, UINT mX, UINT mY, UINT btnId);
void onMouseWheel(char* id, int wheel, UINT mX, UINT mY, UINT btnId, UINT wheels);

void lldSysRender() {
	UINT focusColor;

    for (long i = 0; i <= LLDO_ITERATOR; i++) {
      char* type = LLDO_TYPES[i];
      if (0 == strcmp("itext", type)) {
        edit_box_draw(&LLDO_INP_TEXT[i].ebox);
      }
      if (0 == strcmp("icheckbox", type)) {
        //check_box_draw2(&LLDO_CHB[i].checkbox);
        Icheckbox cb = LLDO_CHB[i];
        landDrawCheckbox(cb);
      }
      if (0 == strcmp("img", type)) {
        Img img = LLDO_IMG[i];
        if (1 == img.tabSupport) {
        	focusColor = LLDI_ALPHA_COLOR;
        	if (img.isInFocus) {
        		focusColor = LLDO_FOCUS_COLOR;
        	}
        	_ksys_draw_bar(img.x, img.y, img.w + 2, img.h + 2, focusColor);
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
      if (0 == strcmp("vscroll", type)) {
        landDrawVScroll(&LLDO_VSCROLL[i].sc, LLDO_VSCROLL[i]);
      }

      if (0 == strcmp("hscroll", type)) {
        landDrawHScroll(&LLDO_HSCROLL[i].sc, LLDO_HSCROLL[i]);
      }

    }

}


void lldSysOnMouseEvent(UINT pressed_button, UINT wheels)
{
	ksys_pos_t mouse_pos;
	uint32_t mouse_button;
	mouse_pos = _ksys_get_mouse_pos(KSYS_MOUSE_WINDOW_POS); // window relative
	mouse_button = _ksys_get_mouse_eventstate();
	int wheel = wheels;
	if (wheels > 10000) {
		wheel = 65535 - wheels;
		if (wheel == 0) {
			wheel = -1;
		} else {
			wheel *= -1;
		}
	}

	UINT mX = (UINT)mouse_pos.x;
	UINT mY = (UINT)mouse_pos.y;
	long btnId = -1;
	char mouseBtn = (char)mouse_button;
	char rType[10];
	char* id = getIdByMousePos(mX, mY, &btnId, rType);
	long cChBIndex = -1;


	if (mouse_button & (1 << 24)) // double click
	{

	}

	for (long i = 0; i <= LLDO_ITERATOR; i++) {
      char* type = LLDO_TYPES[i];

      if (0 == strcmp("itext", type)) {
        edit_box_mouse(&LLDO_INP_TEXT[i].ebox);
      }
      if (0 == strcmp("vscroll", type)) {
        scrollbar_v_mouse(&LLDO_VSCROLL[i].sc);
      }
      if (0 == strcmp("hscroll", type)) {
        scrollbar_h_mouse(&LLDO_HSCROLL[i].sc);
      }
      if (0 == strcmp("icheckbox", type)) {
        cChBIndex = i;
      }
    }

    if (1 == mouseBtn) {
    	onLeftMouseDown(id, mX, mY, pressed_button);
    	prevMouseBtn = 1;
    	if (0 != strcmp("undefined", id)) {
    		setFocus(id, true);
    	}
    }

    if (2 == mouseBtn) {
    	onRightMouseDown(id, mX, mY, pressed_button);
    	prevMouseBtn = 2;
    }

    if (0 == mouseBtn) {
    	if (1 == prevMouseBtn) {
    		if (cChBIndex != -1 && 0 == strcmp("icheckbox", rType)) {
	    		//file_put_contents("chLog.txt", "Clicked!");
	        	landCheckboxOnClickDefaultHandler(cChBIndex);
	        }
    		onClick(id, mX, mY, btnId);
    	}
    	if (2 == prevMouseBtn) {
    		onRightClick(id, mX, mY, pressed_button);
    	}
    	prevMouseBtn = 0;

    	if (wheel != 0) {
    		//onMouseWheel(wheel);
    		onMouseWheel(id, wheel, mX, mY, btnId, wheels);
    	}
    }
    if (prevMX != mX || prevMY != mY) {
    	onMouseMove(id, mX, mY, btnId);
    	prevMX = mX;
    	prevMY = mY;
    }
}


void lldSysOnKeyPressEvent(ksys_oskey_t ch, uint32_t commandKey) {
  BOOL found = false;
  for (long i = 0; i <= LLDO_ITERATOR; i++) {
      char* type = LLDO_TYPES[i];

      if (0 == strcmp("itext", type)) {
        edit_box_key_safe(&LLDO_INP_TEXT[i].ebox, ch);
      }

      if (LLDO_INP_TEXT[i].isInFocus == 1) {
       	onKeyPress(LLDO_INP_TEXT[i].id, ch);
      }

      if (LLDO_BTN[i].isInFocus == 1 && ((uint32_t)ch == 1838336 || (uint32_t)ch == 3743744 )) {
       	onClick(LLDO_BTN[i].id, 0, 0, LLDO_BTN[i].intId);
      }

      if (1 != found) {
        found = landCaptureTab(ch, commandKey);
      }
  }
}