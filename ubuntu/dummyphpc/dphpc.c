#include "dphpc.h"

char* addchar(char* s, char ch) {
	char *r = NULL;
	char ns[2];
	ns[0] = ch;
	ns[1] = 0;
	int nsz = strlen(s) + 2;
	r = malloc(nsz);
	strcpy(r, s);
	strcat(r, ns);
	
	return r;
}

char* addstr(char* s, char* s2) {
	char *r = NULL;
	int nsz = strlen(s) + strlen(s2) + 2;
	r = malloc(nsz);
	strcpy(r, s);
	strcat(r, s2);
	
	return r;
}

char* date(char* fmt) {
	return datets(fmt, 0);
}

char* datets(char* fmt, ULONG ts) {
	time_t t;
	struct tm* now;
	
	if (0 == ts) {
		t = time(0);   // get time now
		now = localtime(&t);
	} else {
		const time_t rawtime = (const time_t)ts;
		now = localtime(&rawtime);
	}
    
	char* o = "HelloworldHelloWorld";
	char* sY = "0123";
	sY = "";
	o = "";
	for (int i = 0; i < strlen(fmt); i++) {
		char c = fmt[i];
		switch (c) {
			case 'Y':
				sY = strval(now->tm_year + 1900);
				o = addstr(o, sY); // TODO
				break;
			case 'm':
				sY = strval(now->tm_mon + 1);
				if (now->tm_mon < 10) {
					sY = addstr("0", sY);
				}
				o = addstr(o, sY);
				break;
			case 'd':
				sY = strval(now->tm_mday);
				if (now->tm_mday < 10) {
					sY = addstr("0", sY);
				}
				o = addstr(o, sY);
				break;
			case 'H':
				sY = strval(now->tm_hour);
				if (now->tm_hour < 10) {
					sY = addstr("0", sY);
				}
				o = addstr(o, sY);
				break;
			case 'i':
				sY = strval(now->tm_min);
				if (now->tm_min < 10) {
					sY = addstr("0", sY);
				}
				o = addstr(o, sY);
				break;
			case 's':
				sY = strval(now->tm_sec);
				if (now->tm_sec < 10) {
					sY = addstr("0", sY);
				}
				o = addstr(o, sY);
				break;
			default:
				o = addchar(o, c);
		}
	}
	
	return o;
}

void logInt(char* file, char* prefix, int n) {
	char sl[255];
	for (int i = 0; i < 255; i++) {
		sl[i] = 0;
	}
	intToStr(n, sl, true);
	writefile(file, prefix, true);
	writefile(file, sl, true);
}

void intToStr(int n, char* sL, BOOL newLine) {
	sprintf(sL, "%d", n);
	ULONG sz = strlen(sL);
	if (sz < 255 && newLine) {
		sL[sz] = '\n';
	}
}

char** explode(char* sep, char* s, int* length) {
	int i, j = 0;
	char ch;
	int slen = strlen(s), sslen = strlen(sep);
	char** res;
	char* buf = "";	

	int L = 0;
	buf = "";
	for (i = 0; i < slen; i++) {
		ch = s[i];
		
		if (ch == sep[j]) {
			++j;
			if (j >= sslen) {
				res = push(res, buf, L);
				j = 0;
				buf = "";
				L++;
			}
		} else {
			buf = addchar(buf, ch);
			j = 0;
		}
	}
	
	res = push(res, buf, L);
	L++;
	
	*length = L;
	return res;
}


char* file_get_contents(char* file) {
	return readfile(file);
}

int file_put_contents(char* file, char* data) {
	return writefile(file, data, false);
}

int file_put_contentsa(char* file, char* data, int mode) {
	if (FILE_APPEND == mode) {
		return writefile(file, data, true);
	}
	
	return writefile(file, data, false);
}

void print_r(char** a, int L) {
	for (int i = 0; i < L; i++) {
		printf("%s\n", a[i]);
	}
}


char** push(char** r, char* s, int L) {
	char **result = NULL;
	int i = 0, j = 0;
	unsigned int ssz = 0;
	for (i = 0; i < L; i++) {
		ssz += strlen(r[i]) + 1;
	}
	ssz += strlen(s) + 1;
	
	result = malloc(2 * ssz);
	
	for (j = 0; j < L; j++) {
		result[j] = r[j];
	}
	
	
	result[j] = s;
	return result;
}

char** pushs(char** r, char* s, int L) {
	return push(r, s, L);
}

char* str_replace(char* search, char* replace, char* subject) {
	int count = -1;
	return str_replacec(search, replace, subject, &count);
}

char* str_replacec(char* search, char* replace, char* subject, int* count) {
	*count = 0;
	int _count = 0;
	
	int i, sptr = 0;
	char* buf = "";
	char* result = "";
	char ch;
	for (i = 0; i < strlen(subject); i++) {
		ch = subject[i];
		if (ch != search[sptr]) {
			sptr = 0;
			if (strlen(buf)) {
				// result += buf;
				result = addstr(result, buf);
				buf = "";
				if (ch == search[0]) {
					// buf += ch;
					buf = addchar(buf, ch);
					sptr++;
					if (sptr > strlen(search) - 1) {
						// result += replace;
						result = addstr(result, replace);
						sptr = 0;
						buf = "";
						_count++;
					}
				} else {
					// result += ch;
					result = addchar(result, ch);
				}
			} else {
				// result += ch;
				result = addchar(result, ch);
			}
		} else {
			//buf += ch;
			buf = addchar(buf, ch);
			sptr++;
			if (sptr > strlen(search) - 1) {
				// result += replace;
				result = addstr(result, replace);
				sptr = 0;
				buf = "";
				_count++;
			}
		}
	}
	
	*count = _count;
	return result;
}

char* strval(int n) {
	char* result = NULL;
	result = malloc(255);
	intToStr(n, result, false);
	
	return result;
}

long strpos(char* haystack, char* needle) {
	return strposo(haystack, needle, 0);
}

long strposo(char* haystack, char* needle, ULONG offset) {
	ULONG i;
	ULONG j = 0;
	char ch;
	ULONG slen = strlen(haystack), sslen = strlen(needle);
	long res = -1;
	char* buf = "";	

	int L = 0;
	buf = "";
	for (i = offset; i < slen; i++) {
		ch = haystack[i];
		
		if (ch == needle[j]) {
			if (j == 0) {
				res = (long)j;
			}
			++j;
			if (j >= sslen) {
				return res;
			}
		} else {
			buf = addchar(buf, ch);
			j = 0;
			res = -1;
		}
	}
	
	return res;	
}
