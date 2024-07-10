//extern vector<string> dphpArgv;
//extern dphpArgv;
#include "dphp.h"
using namespace dphp;

bool isOneDevice(string  t12, string opt);

int main(int argc, char* argv[]) {
	__initRuntime(argc, argv);
	vector<string> output;
	exec("ls -l /dev/disk/by-label", output);
	long sz = count(output);
	string t12 = "", opt = "";
	for (int i = 0; i < sz; i++) {
		string s = output[i];
		if (strpos(s, "T12") != -1) {
			echo("Found Line: " + s);
			vector<string> a = explode("->", s);
			s = a[count(a) - 1];
			a = explode("/", s);
			t12 = a[count(a) - 1];
		}
	}
	
	for (int i = 0; i < sz; i++) {
		string s = output[i];
		if (strpos(s, "OPT") != -1) {
			echo("Found Line: " + s);
			vector<string> a = explode("->", s);
			s = a[count(a) - 1];
			a = explode("/", s);
			opt = a[count(a) - 1];
		}
	}
	
	if (isOneDevice(t12, opt)) {
		string c = file_get_contents("/media/xubuntu/Run/.runmemo.tpl.sh");
		int cntReplace = 0, cntReplace2 = 0;
		c = str_replace("sdd6", opt, c, cntReplace);
		c = str_replace("sdd5", t12, c, cntReplace2);
		cntReplace += cntReplace2;
		cout << "Was " << cntReplace;
		echo(" replacments in .runmemo.tpl.sh");
		file_put_contents("/media/xubuntu/Run/.runmemo.sh", c);
	} else {
		echo("Some then wrong...");
	}
	
	echo("Press a key for close");
	getchar();
	
	return 0;
}


bool isOneDevice(string  t12, string opt) {
	string s1 = substr(t12, 0, 3);
	string s2 = substr(opt, 0, 3);
	return s1 == s2;
}
