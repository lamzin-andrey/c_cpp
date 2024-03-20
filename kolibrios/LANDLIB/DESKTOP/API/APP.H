#include <string.h>
#define MAX_DIR_PATH 4096
typedef struct {
  char dir[MAX_DIR_PATH];
} LLDApp;

LLDApp LANDLIBDESKTOPAPP;

char* Appdir();
void Appinit(int argc, char** argv);