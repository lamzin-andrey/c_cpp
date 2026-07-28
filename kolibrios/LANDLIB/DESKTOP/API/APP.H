#include <string.h>
#include "../../dummyphpc/dphpc.h"
char* LLD_APP_DIR  = "";
int LLD_APP_ARGC  = 0;
char** LLD_APP_ARGS  = NULL;

char* Appinit(int argc, char** argv);
char* Appdir(); // legacy name
char* App_dir(); // actual name
int sApp_dir(char* result, UINT size);
void App_quit();