#include "landio.h"

int writefile(char* filename, char* s, BOOL isAppend) {
	int fd;
	if (isAppend == 1 || isAppend == 8) {
		fd = open(filename, O_CREAT|O_WRONLY|O_APPEND, 0766);
	} else {
		fd = open(filename, O_CREAT|O_WRONLY, 0766);
	}	
	ULONG  sz = (ULONG)strlen(s);
	int result = write(fd, s, sz);
	close(fd);
	return result;
}

int readbuf(char* filename, char* s, ULONG sz, off_t pos) {
	
	for (int i = 0; i < sz; i++) {
		s[i] = '\0';
	}
	
	int fd = open(filename, O_RDONLY);
	
	int sk = (int)lseek(fd, pos, SEEK_CUR);
	
	int result = read(fd, s, sz);
	close(fd);
	return result;
}


char* readfile(char *filename) {
	ULONG bufSize = 7 * 1024 * 1024;
	
	char *r = "";
	char buf[bufSize];
	int nbytes;
	off_t pos = 0;
	do {
		nbytes = readbuf(filename, buf, bufSize, pos);
		if (nbytes == 0) {
			break;
		}
		char *tempR = NULL;
		int ssz = strlen(r) + strlen(buf) + 1;
		tempR = malloc(ssz);
		strcpy(tempR, r);
		strcat(tempR, buf);
		r = tempR;
		
		printf("r = %s", r);
		
		pos += (off_t)nbytes;
	} while(nbytes != 0);
	
	
	return r;
}


/*
 * int main() {
	writefile("HelloC.txt", "A - Hello C!\nPidgin is true animal bird!\n", true);
	char *s;
	s = readfile("HelloC.txt");
	printf("s = %s, r = %d\n", s, 101);
	free(s);
	
	return 0;
}*/
