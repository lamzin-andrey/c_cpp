#include "dphp.h"

long crand() {
	return (long)rand();
}

void dphp::__initRuntime(int argc, char** argv)
{
	dphpArgc = argc;
	for (int i = 0; i < argc; i++) {
		dphpArgv.push_back( string(argv[i]) );
	}
}



void dphp::echo(string s) {
	cout << s << "\n";
}
int dphp::exec(string cmd, vector<string> &output) {
	output.clear();
	string name = dphpArgv[0];
	vector<string> a = explode("/", name);
	name = a[count(a) - 1];
	string out = sys_get_temp_dir() + "/" + name + ".out";
	cmd = cmd + " > " + out + " 2>" + sys_get_temp_dir() + "/" + name + ".err";
	system(cmd.c_str());
	if (file_exists(out)) {
		string c = file_get_contents(out);
		a = explode("\n",  c);
		long sz = count(a);
		for (long i = 0; i < sz; i++) {
			output.push_back(a[i]);
		}
	}
	
	return 0;
}

bool dphp::file_exists(string filename) {
	// #include <unistd.h>
	return ( access( filename.c_str(), F_OK ) != -1 );
}

string dphp::file_get_contents(string file) {
	UtilsStd Lib;
	return Lib.read(file);
}

int dphp::file_put_contents(string file, string data, int mode) {
	UtilsStd Lib;
	return Lib.write(data, file, mode);
}
string dphp::sys_get_temp_dir() {
	// TODO OS!
	return "/tmp";
}

string dphp::date(string fmt, long ts) {
	UtilsStd Lib;
	std::time_t t;
	std::tm* now;
	
	if (!ts) {
		t = std::time(0);   // get time now
		now = std::localtime(&t);
	} else {
		const time_t rawtime = (const time_t)ts;
		now = std::localtime(&rawtime);
	}
    
	string o;
	string sY;
	sY = "";
	o = "";
	for (int i = 0; i < fmt.length(); i++) {
		char c = fmt[i];
		switch (c) {
			case 'Y':
				sY = Lib.intToStr(now->tm_year + 1900);
				o = o + sY;
				break;
			case 'm':
				sY = Lib.intToStr(now->tm_mon + 1, true);
				o = o + sY;
				break;
			case 'd':
				sY = Lib.intToStr(now->tm_mday, true);
				o = o + sY;
				break;
			case 'H':
				sY = Lib.intToStr(now->tm_hour, true);
				o = o + sY;
				break;
			case 'i':
				sY = Lib.intToStr(now->tm_min, true);
				o = o + sY;
				break;
			case 's':
				sY = Lib.intToStr(now->tm_sec, true);
				o = o + sY;
				break;
			default:
				o += c;
		}
	}
	return o;
}
long dphp::rand(long min, long max){
	srand((long)time(NULL));
	return (long)(((double)crand() / RAND_MAX) * (max - min) + min);
}








/*bool dphp::shuffle(vector<int> &a)
{
  long SZ, k, j;
  int b;
  
  SZ = count(a) - 1;
  for(j = 0; j <= SZ; j++){
	k = dphp::rand(0, SZ);
	if(k != j){
	  b = a[j];
	  a[j] = a[k];
	  a[k] = b;
	}
  }
  
  return true;
}

bool dphp::shuffle(vector<long> &a)
{
  long SZ, k, j;
  long b;
  
  SZ = count(a) - 1;
  for(j = 0; j <= SZ; j++){
	k = dphp::rand(0, SZ);
	if(k != j){
	  b = a[j];
	  a[j] = a[k];
	  a[k] = b;
	}
  }
  
  return true;
}

bool dphp::shuffle(vector<double> &a)
{
  long SZ, k, j;
  double b;
  
  SZ = count(a) - 1;
  for(j = 0; j <= SZ; j++){
	k = dphp::rand(0, SZ);
	if(k != j){
	  b = a[j];
	  a[j] = a[k];
	  a[k] = b;
	}
  }
  
  return true;
}*/

string dphp::str_replace(string search, string replace, string subject)
{
	int n = 0;
	return __str_replace(search, replace, subject, n);
}
string dphp::str_replace(string search, string replace, string subject, int &count)
{
	return __str_replace(search, replace, subject, count);
}
string dphp::__str_replace(string search, string replace, string subject, int &count)
{
	
	count = 0;
	
	int i, sptr = 0;
	string buf = "";
	string result = "";
	char ch;
	for (i = 0; i < subject.length(); i++) {
		ch = subject[i];
		if (ch != search[sptr]) {
			sptr = 0;
			if (buf.length()) {
				result += buf;
				buf = "";
				if (ch == search[0]) {
					buf += ch;
					sptr++;
					if (sptr > search.length() - 1) {
						result += replace;
						sptr = 0;
						buf = "";
						count++;
					}
				} else {
					result += ch;
				}
			} else {
				result += ch;
			}
		} else {
			buf += ch;
			sptr++;
			if (sptr > search.length() - 1) {
				result += replace;
				sptr = 0;
				buf = "";
				count++;
			}
		}
	}
	return result;
}

string dphp::substr(string s, int start, int length)
{
	return s.substr(start, length);
}

/**
 * В случае warning Buffer too small можно поместить рядом с файлом php.ini в котором может быть строка fgets_buf_size=N чтобы изменить размерность
 * Знать бы ещё, как его организовать
*/
string dphp::fgets(FILE* f, unsigned int size) {
	/*if (file_exists("php.ini")) {//TODO
		UtilsStd Lib;
		//string phpini = file_get_contents("php.ini");
		string bufSize = _readPhpIniSetting("fgets_buf_size", "0");//TODO
		int newSize = Lib.strToInt(bufSize);
		if (newSize) {
			size = newSize;
		}
	}*/
	char *s = new char[size];
	std::fgets(s, size, f);
	
	string buf(s);
	delete s;
	string result = "";
	// if (buf.length()) {
		/*for (unsigned int n = 0; n < buf.length() - 1; n++) {
			result += buf[n];
		}*/
		result += buf;
	// }
	
	return result;
}


//return -1 if not found
int dphp::strpos(string haystack, string needle, unsigned int offset) {
	UtilsStd Lib;
	return Lib.pos(needle, haystack, offset);
}

vector<string> dphp::explode(string delimeter, string source, unsigned int maxLength) {
	vector<string> arr;
	int n = 0;
	string DEL = "DUMMY_PHP_SPECIAL_DELIMITER_SYMBOL_20200904";
	if (delimeter != "\n") {
		source = str_replace("\n", DEL, source);
		source = str_replace(delimeter, "\n", source);
	}
	string buf = "";
	for (unsigned int i = 0; i < source.length(); i++) {
		if (source[i] == '\n') {
			buf = str_replace(DEL, "\n", buf);
			arr.push_back(buf);
			buf = "";
			n++;
			if (n >= maxLength) {
				return arr;
			}
		} else {
			buf += source[i];
		}
	}
	
	if (buf.length()) {
		buf = str_replace(DEL, "\n", buf);
		arr.push_back(buf);
		n++;
		if (n >= maxLength) {
			return arr;
		}
	}
	
	return arr;
}

string dphp::implode(string glue, vector<string> pieces) {
	string r = "";
	unsigned int sz = pieces.size();
	for (unsigned int i = 0; i < sz; i++) {
		if (i < sz - 1) {
			r += pieces[i] + glue;
		} else {
			r += pieces[i];
		}
	}
	return r;
}

vector<string>  dphp::unset(vector<string> &a, unsigned int index) {
	vector<string> b;
	for (unsigned int i = 0; i < a.size(); i++) {
		if (i != index) {
			b.push_back(a[i]);
		}
	}
	a = b;
	
	return b;
}
