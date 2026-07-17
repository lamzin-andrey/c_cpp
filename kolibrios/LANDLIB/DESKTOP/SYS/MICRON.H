#include "lldvars.h"

UINT currentBtnId = 20;

Element e(char* id);
// TODO  scroll?
Element cine(char* type, char* id, char* path);
Element createIfNotExists(char* type, char* id, char* path);
char* v(char* id, char* val);

char* stl(char* id, char* name, char* value);
char* _setX(Element el, char* val);
char* _setY(Element el, char* val);
char* _setW(Element el, char* val);
char* _setH(Element el, char* val);
char* _setBgColor(Element el, char* val);
char* _setColor(Element el, char* val);
UINT _hexdec(char* val);
char* _setPadding(Element el, char* val);

void setFocus(char* id, BOOL v);
BOOL isFocused(char* id);

/*char* hide(char* id);
char* show(char* id);
char* storage(char* k, char* val);*/