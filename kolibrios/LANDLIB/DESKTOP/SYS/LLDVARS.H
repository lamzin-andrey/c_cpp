#ifndef LANDLIB_DESJKTOP_HEADER
#define LANDLIB_DESJKTOP_HEADER

#include "../../dummyphpc/dphpc.h"
#include "landimage.h"
#define DISPLAY_OBJ_SZ  4096
#define LLDI_DEFAULT_BG_COLOR  0xD2D0C2



typedef struct Itext{
  edit_box ebox;
  char* id;
  char tabIndex;
} Itext;

typedef struct Icheckbox{
  check_box checkbox;
  char* id;
  UINT x;
  UINT y;
  UINT w;
  UINT h;
  char tabIndex;
} Icheckbox;

typedef struct Img{
  char* id;
  UINT x;
  UINT y;
  UINT w;
  UINT h;
  Image* img;
  UINT alphaColor;
  char* src;
  BOOL tabSupport; // 1 - will get and display focus on <TAB>
  char tabIndex;   // -1 - no get focus on <TAB>
} Img;


#define FONT_TYPE10   0
#define FONT_TYPE14   0x10000000
#define FONT_TYPE14B  0x01000000 /** 0x02000000 ? And it 16? */
/*#define FONT_TYPE_A  0x11000000
#define FONT_TYPE_Z  0x17000000
0x07000000 - bold?
*/

typedef struct StaticText{
  char* id;
  UINT x;
  UINT y;
  UINT w;
  UINT h;
  UINT bgColor;
  UINT color;
  UINT borderColor;
  UINT borderWidth;
  char padding;
  char* text;
  char tabIndex;
  UINT fontType;
  UINT savedColor;
} StaticText;


char*        LLDO_TYPES[DISPLAY_OBJ_SZ];
Itext        LLDO_INP_TEXT[DISPLAY_OBJ_SZ];
Icheckbox    LLDO_CHB[DISPLAY_OBJ_SZ];
Img          LLDO_IMG[DISPLAY_OBJ_SZ];
StaticText   LLDO_TEXT[DISPLAY_OBJ_SZ];
long         LLDO_ITERATOR = -1;

char prevMouseBtn = 0;
UINT prevMX = 0;
UINT prevMY = 0;

#endif /* KOLIBRI_BOXLIB_H */