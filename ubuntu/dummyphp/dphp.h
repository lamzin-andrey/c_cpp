#ifndef DPHP_H
#define DPHP_H

#define FILE_APPEND 9

#include "utilsstd.h"
#include <unistd.h>
#include <vector>
#include <ctime>


static vector<string> dphpArgv;
static int dphpArgc;

long crand();


namespace dphp {
	void __initRuntime(int argc, char** argv);
	string date(string fmt, long ts = 0);
	void echo(string s);
	int exec(string cmd, vector<string> &output);
	vector<string> explode(string delimeter, string source, unsigned int maxLength = 1000000);
	//TODO can use php.ini в котором может быть строка fgets_buf_size=N
	string fgets(FILE* f, unsigned int  = 2048);
	bool file_exists(string filename);
	string file_get_contents(string file);
	string implode(string glue, vector<string> pieces);
	//9 for append
	int file_put_contents(string file, string data, int mode = 0);
	long rand(long min, long max);
	
	template<typename T> long count(vector<T> a);
	template<typename T> long count(vector<T> a) {
		return a.size();
	}
	
	template<typename T> bool shuffle(vector<T> &a);
	template<typename T> bool shuffle(vector<T> &a)
	{
	  long SZ, k, j;
	  T b;
	  
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
	/*bool shuffle(vector<int> &output);
	bool shuffle(vector<long> &output);
	bool shuffle(vector<double> &output);*/
	
	
	string sys_get_temp_dir();
	string str_replace(string search, string replace, string subject, int &count);
	string str_replace(string search, string replace, string subject);
	string __str_replace(string search, string replace, string subject, int &count);
	//return -1 if not found
	string substr(string s, int start, int length);
	int strpos(string haystack, string needle, unsigned int offset = 0);
	vector<string> unset(vector<string> &a, unsigned int index);
}

#endif
