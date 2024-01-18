#include <asm-generic/fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long ULONG;
typedef char BOOL;
#define true 1
#define false 0

int writefile(char* filename, char* s, BOOL isAppend);
int readbuf(char* filename, char* s, ULONG sz, off_t pos);
char* readfile(char *filename);
