#include "mw.h"
void MWmoveTo(unsigned int x, unsigned int y) {
	winX = x;
	winY = y;
	_ksys_change_window(winX, winY, winW, winH);
}
void MWresizeTo(unsigned int w, unsigned int h) {
	winW = w;
	winH = h;
	_ksys_change_window(winX, winY, winW, winH);
}
void MWsetTitle(char* s) {
	_ksys_set_window_title(s);
}