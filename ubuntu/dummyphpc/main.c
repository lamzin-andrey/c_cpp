#include "dphpc.h"

int main() {
	int L = -1;
	char** a = explode("\n", file_get_contents("dphpc.c"), &L);
	printf("amain L = %d\n", L);
	print_r(a, L);
	
	puts( date("Y-m-d H:i:s\n") );
	
	file_put_contents("helloPhpC.txt", "ONE\n");
	char* str = file_get_contents("helloPhpC.txt");
	puts(str);
	
	file_put_contentsa("helloPhpC.txt", "Seal!\n", 8);
	str = file_get_contents("helloPhpC.txt");
	puts(str);
	
	str = "Hello World!\n";
	int N = -1;
	str = str_replacec("o", "Wass", str, &N);
	puts(str);
	printf("N= %d\n", N);
	
	long LN = strpos(str, "d");
	printf("strpos = %ld\n", LN);
	
	return 0;
}
