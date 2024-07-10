#ifndef DPHP_H
#define DPHP_H

#define FILE_APPEND 9

#include "utilsstd.h"
#include <unistd.h>
#include <vector>
#include <ctime>

static vector<string> dphpArgv;
static int dphpArgc;


namespace dphp {
	void __initRuntime(int argc, char** argv);
	long count(vector<string> a);
	string date(string fmt, long ts = 0);
	void echo(string s);
	int exec(string cmd, vector<string> &output);
	//9 for append
	string file_get_contents(string file);
	int file_put_contents(string file, string data, int mode = 0);
	string sys_get_temp_dir();
	string str_replace(string search, string replace, string subject, int &count);
	string str_replace(string search, string replace, string subject);
	string __str_replace(string search, string replace, string subject, int &count);
	string substr(string s, int start, int length);
	//TODO can use php.ini в котором может быть строка fgets_buf_size=N
	string fgets(FILE* f, unsigned int  = 2048);
	//return -1 if not found
	int strpos(string haystack, string needle, unsigned int offset = 0);
	bool file_exists(string filename);
	vector<string> explode(string delimeter, string source, unsigned int maxLength = 1000000);
	string implode(string glue, vector<string> pieces);
	vector<string> unset(vector<string> &a, unsigned int index);
}

#endif
