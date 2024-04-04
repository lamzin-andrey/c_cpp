// BOXLIB EXAMPLE (scrollbar, progressbar, editbox and checkbox)
// Writed by maxcodehack and superturbocat2001

#include <sys/ksys.h>
#include <clayer/boxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ksys.h>
#define WIN_W 640
#define WIN_H 563
#define ED_BUFF_LEN 50
#define TEXT_SIZE 0x10000000
#define SCROLL_BUTTON_SIZE 15
#define SCROLL_MAX_LEN 215
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define BLUE 0x0000FF
#define X_W(X, W) ((X << 16) + W)
#define Y_H X_W


ksys_thread_t proc_info;
#include "landlib/desktop/sys/lldyscontroller.c" // listeners

#include "landlib/desktop/api/mw.c" // api
#include "app/appcontroller.c" // it functions call landsyscontroller



uint32_t wheels;
uint32_t pressed_button;

char* title = "Boxlib example";
char wndWasCentred = 0;


// TODO appcontroller::layout
// Начнем с простого: поместим в соотв. массивы подобные переменные.

void draw_window()
{

    _ksys_start_draw();
    _ksys_create_window(15, 100, WIN_W, WIN_H, title, /*0x858585*//*0xEFE9D6*/0xD2D0C2, 0x13);//0x13 was 0x34 - fixed

    // set in cenbter
    if (wndWasCentred == 0) {
    	ksys_pos_t sz = _ksys_screen_size();
    	winX = (sz.x - WIN_W) / 2;
    	winY = (sz.y - WIN_H) / 2;
    	wndWasCentred = 1;
    	_ksys_change_window(winX, winY, winW, winH);
    }



    _ksys_thread_info(&proc_info, -1);

    lldSysRender();	// LLD

    _ksys_end_draw();
}

int main()
{
	winW = 640;
	winH = 563;
	winX = 15;
	winY = 100;
    onCreate(); // LLD

    _ksys_set_event_mask(KSYS_EVM_REDRAW + KSYS_EVM_KEY + KSYS_EVM_BUTTON + KSYS_EVM_MOUSE + KSYS_EVM_MOUSE_FILTER);
    while (1) {

        switch (_ksys_get_event()) {
        case KSYS_EVENT_BUTTON:
        	pressed_button = _ksys_get_button();
            if (pressed_button == 1)
                return 0;
            break;

        case KSYS_EVENT_KEY:
            lldSysOnKeyPressEvent(_ksys_get_key(),  _ksys_get_control_key_state()); // LLD
            draw_window();
            break;

        case KSYS_EVENT_REDRAW:
            draw_window();
            break;

        case KSYS_EVENT_MOUSE:
        	if (0 == pressed_button) {
				pressed_button = _ksys_get_button();
			}


            wheels = _ksys_get_mouse_wheels();

            lldSysOnMouseEvent(pressed_button, wheels); // LLD

            break;
        }
    }
    return 0;
}
