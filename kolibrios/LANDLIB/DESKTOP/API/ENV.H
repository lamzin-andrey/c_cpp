#include <clayer/dialog.h>
#include <sys/ksys.h>
#include <string.h>





char* Env_openFileDialog(char* caption, char*dir, char* filter);
char* Env_saveFileDialog(char* caption, char*dir, char* filter);
char* Env_openDirectoryDialog(char* caption, char*dir);

int sEnv_openFileDialog(char* caption, char*dir, char* filter, char* result, unsigned int size);
int sEnv_saveFileDialog(char* caption, char*dir, char* filter, char* result, unsigned int size);
int sEnv_openDirectoryDialog(char* caption, char*dir, char* result, unsigned int size);

int Env_exec1(char* exe, char* args);
void Env_kill(unsigned long id);

// private
od_filter* Env_getODFilter(char* filter);

