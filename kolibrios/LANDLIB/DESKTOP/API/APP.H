#include <string.h>
#include "../../dummyphpc/dphpc.h"
char* LLD_APP_DIR  = "";

char* Appinit(int argc, char** argv);
char* Appdir(); // legacy name
char* App_dir(); // actual name
int sApp_dir(char* result, UINT size);