#include "app.h"

char* Appdir() {
	return LANDLIBDESKTOPAPP.dir;
}

void Appinit(int argc, char** argv) {
  char path[MAX_DIR_PATH];
  int sz = strlen(argv[0]);
  int sz2;

  // Search last /
  for (int i = sz - 1; i > -1; i--) {
    if (argv[0][i] == '/') {
      break;
    }
    sz2 = i;
  }
  if (sz2 > 0) {
    sz2--;
  }

  for (int i = 2, j = 0; i < sz2; i++, j++) {
    LANDLIBDESKTOPAPP.dir[j] = argv[0][i];
  }
}