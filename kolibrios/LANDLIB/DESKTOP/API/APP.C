#include "app.h"

char* Appinit(int argc, char** argv) {
	if (argc > 0) {
		char* slf = argv[0];
		slf = substr(slf, 2);
		int L = -1;
		char** ls = explode("/", slf, &L);
		unseta(ls, L - 1, &L);
		slf = implode("/", ls, L);
		free(ls);
		LLD_APP_DIR = slf;
	}
}
char* Appdir() {
	return LLD_APP_DIR;
}

char* App_dir() {
	return Appdir();
}

int sApp_dir(char* result, UINT size) {
	if (strlen(LLD_APP_DIR) > size) {
		return 0;
	}

	strcpy(result, LLD_APP_DIR);

	return 1;
}