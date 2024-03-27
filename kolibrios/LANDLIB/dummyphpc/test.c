#include "dphpc.h"

void testExplode() {
	int L = -1;
	char** a = explode("\n", file_get_contents("testfile.txt"), &L);
	if (L == 303) {
		printf("explode(1)OK\n");
	} else {
		printf("Fail explode(1), got %d, expect 303\n", L);
	}
	
	char path[255] = "/sd0/1/lives/kolibri/hdata/coding/c/customize/customize.kex";
	char sep[255] = "customize.kex";
	char** ab = explode(sep, path, &L);
	if (L == 2) {
		printf("explode(2)OK\n");
	} else {
		printf("Fail explode(2), got %d, expect 2\n", L);
	}
	
	if (0 == strcmp(ab[1],"")) {
		printf("explode(3)OK\n");
	} else {
		printf("Fail explode(3), got `%s`, expect ``\n", ab[1]);
	}
	
	if (0 == strcmp(ab[0],"/sd0/1/lives/kolibri/hdata/coding/c/customize/")) {
		printf("explode(4)OK\n");
	} else {
		printf("Fail explode(4), got `%s`, expect `/sd0/1/lives/kolibri/hdata/coding/c/customize/`\n", ab[0]);
	}
}

void testDate() {
	char* date1 = date("Y-m-d H:i:s");
	sleep(1);
	char* date2 = date("Y-m-d H:i:s");
	int sz = strlen(date1), i;
	
	puts( date("Y-m-d H:i:s\n") );
	
	if (sz == 19) {
		printf("date(1)OK\n");
	} else {
		printf("Fail date(1), got `%d`, expect 19\n", sz);
	}
	
	int cmpv = strcmp(date2, date1);
	if (1 == cmpv) {
		printf("date(2)OK\n");
	} else {
		printf("Fail date(2), got `%d`, expect 1\n", cmpv);
	}
}

void testFPGC() {
	file_put_contents("helloPhpC.txt", "ONE\n");
	char* str = file_get_contents("helloPhpC.txt");
	int cmpv = strcmp(str, "ONE\n");
	if (0 == cmpv) {
		printf("file_put_contents(1)OK\n");
	} else {
		printf("Fail file_put_contents(1), got `%d`, expect 0\n", cmpv);
	}
	
	file_put_contentsa("helloPhpC.txt", "Seal!\n", 8);
	str = file_get_contents("helloPhpC.txt");
	cmpv = strcmp(str, "ONE\nSeal!\n");
	if (0 == cmpv) {
		printf("file_put_contents(2)OK\n");
	} else {
		printf("Fail file_put_contents(2), got `%d`, expect 0\n", cmpv);
	}
}

void testStrReplace() {
	char* str = "Hello World!\n";
	int N = -1;
	str = str_replacec("o", "Wass", str, &N);
		
	int cmpv = strcmp(str, "HellWass WWassrld!\n");
	if (0 == cmpv) {
		printf("str_replacec OK\n");
	} else {
		printf("Fail str_replacec, got `%d`, expect 0\n", cmpv);
	}
	
	if (2 == N) {
		printf("str_replace OK\n");
	} else {
		printf("Fail str_replace, got `%d`, expect 2\n", N);
	}
	
	
	char* str2 = "Hello World!\n";
	int N2 = -1;
	str2 = str_replacec("o", "Wosso", str2, &N2);
	//puts(str2);
		
	cmpv = strcmp(str2, "HellWosso WWossorld!\n");
	if (0 == cmpv) {
		printf("str_replacec OK\n");
	} else {
		printf("Fail str_replacec, got `%d`, expect 0\n", cmpv);
	}
	
	if (2 == N2) {
		printf("str_replace OK\n");
	} else {
		printf("Fail str_replace, got `%d`, expect 2\n", N);
	}
}


void testStrpos() {
	char* str = "HellWass WWassrld!\n";
	long LN = strpos(str, "d");
	//printf("strpos = %ld\n", LN);
	if (16 == LN) {
		printf("strpos(1) OK\n");
	} else {
		printf("Fail strpos(1), got `%ld`, expect 16\n", LN);
	}
	
	LN = strpos(str, "assrl");
	//printf("strpos = %ld\n", LN);
	if (11 == LN) {
		printf("strpos(2) OK\n");
	} else {
		printf("Fail strpos(2), got `%ld`, expect 11\n", LN);
	}
	
	LN = strpos(str, "H");
	// printf("strpos = %ld\n", LN);
	if (0 == LN) {
		printf("strpos(3) OK\n");
	} else {
		printf("Fail strpos(3), got `%ld`, expect 0\n", LN);
	}
	
	LN = strpos(str, "Qws");
	// printf("strpos = %ld\n", LN);
	if (-1 == LN) {
		printf("strpos(4) OK\n");
	} else {
		printf("Fail strpos(4), got `%ld`, expect -1\n", LN);
	}
}

int main() {
	testExplode();
	testDate();
	testFPGC();
	testStrReplace();
	testStrpos();
	
	return 0;
}
