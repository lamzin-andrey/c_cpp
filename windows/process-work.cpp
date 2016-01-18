//Список запущенных процессов на cpp
//Компилировалось с помощью g++ for windows c++ 98
//Заголовочные файлы явно многие лишние

#include <windows.h>
#include <tlhelp32.h>
//#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <io.h>
using namespace std;

bool processExist(string processFileName) {
	PROCESSENTRY32 Entry;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    Entry.dwSize = sizeof(Entry);
    Process32First(hSnapshot, &Entry);
    do {
		string a = Entry.szExeFile;		
		if (a == processFileName) {
			return true;
		}
		//cout << Entry.th32ProcessID << "\t" << Entry.szExeFile << "\n";
    } while (Process32Next(hSnapshot, &Entry ) );	
	return false;
}
