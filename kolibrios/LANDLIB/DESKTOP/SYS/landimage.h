#ifndef LANDLIB_IMAGE_HEADER
#define LANDLIB_IMAGE_HEADER

#include <clayer/libimg.h>
#include "../../dummyphpc/dphpc.h"

#define LLD_IMAGES_SZ  4096

char*        LLDI_SRC[LLD_IMAGES_SZ];
Image        LLDI_IMAGES[LLD_IMAGES_SZ];
long         LLDI_ITERATOR = -1;
UINT         LLDI_ALPHA_COLOR = 0xD2D0C2;

char*       logFile = "logImg.txt";

// ����� ⮫쪮 ��⮤�, ����㦠�騥 � ���᫢뢠�騥 ����ࠦ����. ���⮬� � ��� ��䨪� Draw
// ���� �⮣� � ������ࠬ� ��� ७��ਭ�� �१ LLDO_TYPES ⠬ ��, ��� � ���� ��⠫쭮� GUI

// public
/**
 * ��⮬���᪨ ����⠡���� ����� �� �ਭ�.
*/
void landDrawImageW(char* src, UINT x, UINT y, UINT w);
void landDrawImage(char* src, UINT x, UINT y, UINT w); // alias for void landDrawImageW
void setAlphaColor(UINT alphaColor);
/**
 * ��⮬���᪨ ����⠡���� �ਭ� �� ����.
*/
//void landDrawImageH(char* src, UINT x, UINT y, UINT h);
/**
 * ����⠡���� � ����� � 訨ਭ�
*/
void landDrawImageWH(char* src, UINT x, UINT y, UINT w, UINT h);
/**
 * ����⠡���� � ����� �� �ਭ�, �������� � ��業��.
*/
//void landDrawImageWP(char* src, UINT x, UINT y, char w);

/**
 * ����⠡���� �ਭ� �� ����, �������� � ��業��.
*/
//void landDrawImageHP(char* src, UINT x, UINT y, char h);

/**
 * ����⠡���� � ����� � 訨ਭ� ��।��� � ��業��.
*/
//void landDrawImageWHP(char* src, UINT x, UINT y, char w, char h);

/**
 * ���� �뢮��� ��� ����.
*/
void landDrawImageN(char* src, UINT x, UINT y);


// private
void* landImgLoadPngFromFile(char* file, uint32_t* read_sz);
Image* landImgPreparePngData(void* fileData, uint32_t* imgSize);
Image* landImgFind(char* src);


#endif /* LANDLIB_IMAGE_HEADER */