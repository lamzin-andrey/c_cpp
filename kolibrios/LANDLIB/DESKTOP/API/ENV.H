#include <clayer/dialog.h>
#include <sys/ksys.h>
#include <string.h>

char* EnvopenFileDialog(char* caption, char*dir, char* filter);
char* EnvopenDirectoryDialog(char* caption, char*dir);

int Envexec1(char* exe, char* args);
void Envkill(unsigned long id);
