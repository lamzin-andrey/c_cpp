#ifndef LANDLIB_DESJKTOP_HEADER
#define LANDLIB_DESJKTOP_HEADER

#include <sys/ksys.h>
#include <clayer/boxlib.h>
//#include <clayer/libimg.h>


#include "../../dummyphpc/dphpc.h"
#include "landimage.h"
#define DISPLAY_OBJ_SZ  4096
#define LLDI_DEFAULT_BG_COLOR  0xD2D0C2

int winW;
int winH;
int winX;
int winY;

int focusedTabIndex = -1;
char TabIndexDefaultMode = 0; // 0 - images and static text no get focus on tab
 							  // 1 - images get focus on tab,  static text no get focus on tab
 							  // 2 - images no get focus on tab,  static text get focus on tab
 							  // 3 - images and static text get focus on tab
long LLDO_TAB_INDEX = -1;
UINT LLDO_FOCUS_COLOR = 0x0000FF;

typedef struct Itext{
  edit_box ebox;
  char* id;
  char* text;
  int tabIndex;
  char isInFocus;
} Itext;

Itext* focusedItext;


typedef struct Icheckbox{
  //check_box checkbox;
  char* id;
  char state; // 0 - unchecked, 1 - checked, 2 - rollover unchecked, 3 - rollover nchecked, 4 - square
  char* label;
  UINT x;
  UINT y;
  UINT w;
  UINT wI;
  UINT h;
  UINT marginRight;
  int tabIndex;
  char isInFocus;
  UINT fontType;
} Icheckbox;

Icheckbox* focusedIcheckbox;

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
  int tabIndex;   // -1 - no get focus on <TAB> and left click
  char isInFocus;
} Img;

Img* focusedImg;


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
  int tabIndex;
  UINT fontType;
  UINT savedColor;
} StaticText;

typedef struct LLDButton{
  char* id;
  UINT intId;
  UINT x;
  UINT y;
  UINT w;
  UINT h;
  UINT bgColor;
  UINT color;
  char* text;
  int tabIndex;
  char isInFocus;
  UINT fontType;
  UINT savedColor;
} LLDButton;

LLDButton* focusedLLDButton;

#define LLD_SCROLL_WIDTH 15
typedef struct VScroll{
	char* id;
	int x;
	int h;
	UINT offsetY;
	char hasNormal; // set 1 if block has hscroll (Else will intersect)
	scrollbar sc;
	int tabIndex;
} VScroll;

typedef struct HScroll{
	char* id;
	int y;
	int w;
	UINT offsetX;
	char hasNormal; // set 1 if block has vscroll (Else will intersect)
	scrollbar sc;
	int tabIndex;
} HScroll;


typedef struct Element {
	char* type;
	Img* img;
	Icheckbox* cb;
	Itext* iText;
	StaticText* txt;
	LLDButton* btn;
	VScroll* vs;
	HScroll* hs;
} Element;

Element currentEl;


char*        LLDO_TYPES[DISPLAY_OBJ_SZ];
Itext        LLDO_INP_TEXT[DISPLAY_OBJ_SZ];
Icheckbox    LLDO_CHB[DISPLAY_OBJ_SZ];
Img          LLDO_IMG[DISPLAY_OBJ_SZ];
StaticText   LLDO_TEXT[DISPLAY_OBJ_SZ];
LLDButton    LLDO_BTN[DISPLAY_OBJ_SZ];
VScroll      LLDO_VSCROLL[DISPLAY_OBJ_SZ];
HScroll      LLDO_HSCROLL[DISPLAY_OBJ_SZ];
long         LLDO_ITERATOR = -1;

char prevMouseBtn = 0;
UINT prevMX = 0;
UINT prevMY = 0;

#endif /* KOLIBRI_BOXLIB_H */