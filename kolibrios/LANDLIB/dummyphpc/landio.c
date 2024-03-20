#include "landio.h"

int writefile(char* filename, char* s, BOOL isAppend) {
	FILE *fd;
	if (isAppend == 1 || isAppend == 8) {
		fd = fopen(filename, "a");
	} else {
		fd = fopen(filename, "w");
	}
	ULONG  sz = (ULONG)strlen(s);
	int result = fwrite(s, sizeof(char),sz, fd);
	fclose(fd);
	return sz;
}



char* readfile(char *filename) {

	ULONG bufSize = 4*1024;

	char *r = "";
	char buf[bufSize];


	FILE *f;
	char* rdResult;

	f = fopen(filename, "r");
	while (NULL != rdResult && EOF != feof(f)){
		// puts("do gets\n");
		for (ULONG i = 0; i < bufSize; i++) {
		   buf[i] = '\0';
	 	}
		rdResult = fgets(buf, bufSize, f);
		// printf("buf = `%s`\n", buf);

		char *tempR = NULL;
		int ssz = strlen(r) + strlen(buf) + 1;
		tempR = malloc(ssz);
		strcpy(tempR, r);
		strcat(tempR, buf);
		r = tempR;

	}
	fclose(f);

	return r;
}

