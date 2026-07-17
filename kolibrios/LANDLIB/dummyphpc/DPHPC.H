#include "landio.h"
#include <time.h>
#include <limits.h>

#define FILE_APPEND 8
#define PHP_INT_MAX  INT_MAX;

// PHP
char* date(char* fmt);
char* datets(char* fmt, ULONG ts);
char* dechex(UINT v);
char** explode(char* sep, char* s, int* length);
char* implode(char* sep, char** ls, int length);
BOOL file_exists(char* filename);
char* file_get_contents(char* file);
int file_put_contents(char* file, char* data);
int file_put_contentsa(char* file, char* data, int mode);
UINT hexdec(char* v);
char* _setHexSymbol(char* s , int i, UINT v);
UINT _getByteFromCh(char c);
long intval(char* v);
// char* PHPfgets(int fd, ULONG size);
char** push(char** arr, char* s, int L);
char** pushs(char** arr, char* s, int L);
void unseta(char** list, int index, int* length);
void print_r(char** a, int L);
char* str_replacec(char* search, char* replace, char* subject, int* count);
char* str_replace(char* search, char* replace, char* subject);
char* strval(int n);
//return -1 if not found
long strposo(char* haystack, char* needle, ULONG offset);
long strpos(char* haystack, char* needle);
//char* substrl(char* str, int offset, int length);
//char* substr(char* str, int offset);
char* trim(char* s);

// start function for crypton
unsigned int* uipush(unsigned int* a, unsigned int n, unsigned int* L);
int* ipush(int* a, int n, int* L);
char* substr(char* string, int offset, int* length);
char chr(int n);
int ord(char c);
// end function for crypton

// utils
char* addchar(char* s, char ch);
char* addstr(char* s, char* s2);
void intToStr(int n, char* sL, BOOL newLine);
void logInt(char* file, char* prefix, int n);
void logFloat(char* file, char* prefix, double n);
void logStr(char* file, char* prefix, char* str);
BOOL es(char* s1, char* s2);
