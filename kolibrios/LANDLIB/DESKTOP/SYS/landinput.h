#include <sys/ksys.h>
#include <clayer/boxlib.h>

#define TEXT_SIZE 0x10000000
#define X_W(X, W) ((X << 16) + W)
#define Y_H X_W


#include "lldvars.h" // ��� ���ᨢ�.
//#include "landimage.h"

ksys_colors_table_t sys_color_table;

void landButtonA(char id);
void landButtonB(int id);

void lldIText(char* id, UINT x, UINT y, char* val);
void lldITextS(char* id, UINT  x, UINT  y, UINT  w, UINT  h, char* val);
void lldITextSC(char* id, UINT  x, UINT  y, UINT  w, UINT  h, char* val, UINT  bgColor, UINT color);

void lldICheckbox(char* id, UINT x, UINT y, char* val);
void lldICheckboxC(char* id, UINT x, UINT y, char* label, UINT  bgColor, UINT color);

Img* lldImg(char* id, char* src, UINT x, UINT y, UINT w);
Img* lldImgC(char* id, char* src, UINT x, UINT y, UINT w, UINT alphaColor);

StaticText* lldText(char* id, char* val, UINT x, UINT y);
StaticText* lldTextP(char* id, char* val, UINT x, UINT y, char padding);
StaticText* lldTextPB(char* id, char* val, UINT x, UINT y, char padding, UINT borderColor, UINT borderWidth);
StaticText* lldTextPBC(char* id, char* val, UINT x, UINT y, char padding, UINT borderColor, UINT borderWidth, UINT bgColor, UINT color);
StaticText* lldLabel(char* id, char* val, UINT x, UINT y, UINT bgColor, UINT color);
StaticText* lldLabelB(char* id, char* val, UINT x, UINT y, UINT bgColor, UINT color, UINT borderWidth, UINT bgColor);
