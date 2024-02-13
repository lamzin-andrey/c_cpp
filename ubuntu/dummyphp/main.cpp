#include "dphp.h"
using namespace dphp;

int main(int argc, char** argv){
	/*string s = file_get_contents("main.cpp");
	cout << s << "\n";
	int n = file_put_contents("out.work", s + "\n" + date("Y-m-d H:i:s", 1517331203));
	cout << "writed " << n << "bytes...\n";*/
	
	int n = 0;
	string s = str_replace("hum", "RE", "dumhummy and hum was snippet and hummerhum", n);
	s = str_replace("hul", "RE", "dumhummy and hum was snippet and hummerhum", n);
	s = str_replace("hum", "RE", "dumhummy and hum was snippet and hummerhum");
	cout << "s = " << s << "\n";
	cout << "n = " << n << "\n";
	return 0;
}
