extern "C" {
 #include "landio.h"
}
#include <string>
using namespace std;

int main() {
	
	string file = "cfile.txt";
	string str= "My wonderful world\n";
	
	writefile((char*)file.c_str(), (char*)str.c_str(), 0);
	
	// winkl();
	
	return 0;
}
