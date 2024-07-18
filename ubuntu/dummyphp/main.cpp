#include "dphp.h"
using namespace dphp;



int main(int argc, char** argv){
	cout << dphp::rand(5, 10) << "\n";
	vector<long> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);
	a.push_back(6);
	long sz = shuffle(a);
	for (long i = 0; i < count(a); i++) {
		cout << a[i] << "\n";
	}
	/*string s = file_get_contents("main.cpp");
	cout << s << "\n";
	int n = file_put_contents("out.work", s + "\n" + date("Y-m-d H:i:s", 1517331203));
	cout << "writed " << n << "bytes...\n";
	
	int n = 0;
	string s = str_replace("hum", "RE", "dumhummy and hum was snippet and hummerhum", n);
	s = str_replace("hul", "RE", "dumhummy and hum was snippet and hummerhum", n);
	s = str_replace("hum", "RE", "dumhummy and hum was snippet and hummerhum");
	cout << "s = " << s << "\n";
	cout << "n = " << n << "\n";*/
	return 0;
}
