#include "../dummyphpc/dphpc.h"

#define LAND_CRYPTON_FW "UTF-8"

// не надо менять, вся работа происходит в однобайтной кодировке.
// #define CP1251 "WINDOWS-1251";

// TODO в H файл
typedef struct {
	BOOL abcIsInitalize;
	unsigned int* Map;
	unsigned int  L;
	unsigned int  b;
} SLandEncrypt;

typedef struct {
	char* abc;
	unsigned int* m;
	unsigned int msz;
	unsigned int  L;
	unsigned int  b;
} SVocArg;

char*  LandCryptonCrypt(char* s, char* password);
char* LandCryptonDecrypt(char* s, char* password);
void  LandCryptonInitAbc(char* password, SVocArg*f);
int LandCryptonArrIndexOf(UINT* a, UINT b, UINT L);
BOOL  LandCryptonValidPassword(char* c, char* b);
char* LandCrypton_decrypt(char* t, char* password);
char LandCryptonFromCharCode(int e, int a, SVocArg b);
char*  LandCryptonCharCode(char* h, unsigned int f, SVocArg d);
unsigned int  LandCryptonGetLimit(int a, SVocArg* c, int b);
int  LandCryptonGetLimitN(int d, SVocArg* f);
