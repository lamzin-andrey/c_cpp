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
	title = s;
	_ksys_set_window_title(s);
}

void MW_maximize() {
	IntRect r = zMW_getViewport();
	_ksys_change_window(r.x, r.y, r.w, r.h);
}
void MWmaximize() {
	MW_maximize();
}

// private
IntRect zMW_getViewport() {
	int a, b, left, right, top, btm, buf;
	asm_inline(
        "int $0x40"
        : "=a"(a), "=b"(b)
        : "a"(48), "b"(5)
	);
	buf = a;
	buf = buf << 16;
	buf = buf >> 16;
	right = buf;

	buf = a;
	buf = buf >> 16;
	buf = buf << 16;
	left = buf;

	buf = b;
	buf = buf << 16;
	buf = buf >> 16;
	btm = buf;

	buf = b;
	buf = buf >> 16;
	buf = buf << 16;
	top = buf;

	IntRect r;
	r.x = left;
	r.y = top;
	r.w = right - left;
	r.h = btm - top;

	return r;
}