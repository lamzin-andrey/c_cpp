#include "../sys/lldvars.h"
void MWmoveTo(unsigned int x, unsigned int y);
void MWresizeTo(unsigned int w, unsigned int h);
void MWsetTitle(char* s);

void MW_maximize();
void MWmaximize();

// private
IntRect zMW_getViewport();