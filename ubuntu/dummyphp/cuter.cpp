#include "dphp.h"
using namespace dphp;

int main(int argc, char* argv[]) {
	
	if (!dphp::file_exists("config.txt")) {
		cout << "config.txt not found near cuter.run\n";
		return 0;
	}
	string config = dphp::file_get_contents("config.txt");
	vector<string> aConf = dphp::explode("\n", config);
	if (aConf.size() < 3) {
		cout << "wrong config.txt:\nExpected First string - input file\nSecond string - output file\nThird string and more - search value";
		return 0;
	}
	
	string file = aConf[0];
	if (!dphp::file_exists(file)) {
		cout << "file " << file << " not found!\n";
		return 0;
	}
	string outfile = aConf[1];
	
	file_put_contents(outfile, "");
	if (!dphp::file_exists(outfile)) {
		cout << "Unable created " << outfile << "\n";
		return 0;
	}
	
	dphp::unset(aConf, 0);
	dphp::unset(aConf, 0);
	string del = "\n";
	string search = dphp::implode(del, aConf);
	
	
	FILE *h = fopen(file.c_str(), "r");
	
	int n = 0;
	while (!feof(h)) {
		string s = dphp::fgets(h);
		// cout << "n " << n << "s = '" << s << "'\n";
		if (dphp::strpos(s, search) != -1) {
			file_put_contents(outfile, (s + "\n"), 9);
		}
		n++;
	}
	fclose(h);
}
