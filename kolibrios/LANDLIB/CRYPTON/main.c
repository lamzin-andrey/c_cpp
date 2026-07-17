#include "crypton.h"

int main() {
	char* s = file_get_contents("README.TXT");

	char* pass = "1Io01545";
	char* cr = "";
	char* de = "";


	cr = LandCryptonCrypt(s, pass);
	printf("cr = %s\n\n", cr);
	de = LandCryptonDecrypt(cr, pass);
	printf("de = %s\n\n", de);
	file_put_contents("README.CRYPT.txt", cr);
	file_put_contents("README.DECRYPT.txt", de);
	return 0;
}
