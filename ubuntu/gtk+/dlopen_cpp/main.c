#include <dlfcn.h>

int main(int argc, char* argv[]){

	void *ext_library;	// хандлер внешней библиотеки
	long value=0;		// значение для теста
	long (*powerfunc)(long x);	// переменная для хранения адреса функции

	//загрузка библиотеки
	ext_library = dlopen("/usr/lib/libgtk-x11-2.0.so",RTLD_LAZY);
	if (!ext_library){
		//если ошибка, то вывести ее на экран
		//fprintf(stderr,"dlopen() error: %s\n", dlerror());
		return 1;
	};

	//загружаем из библиотеки требуемую процедуру
	powerfunc = dlsym(ext_library, "gtk_window_new");	
	value=3;

	//выводим результат работы процедуры
	printf("%s(%f) = %f\n",argv[1],value,(*powerfunc)(value));

	//закрываем библиотеку
	dlclose(ext_library);
}


/*C++ variant*/

#include <iostream>
#include <dlfcn.h>

int main() {
    using std::cout;
    using std::cerr;

    cout << "C++ dlopen demo\n\n";

    // open the library
    cout << "Opening hello.so...\n";
    void* handle = dlopen("./hello.so", RTLD_LAZY);
    
    if (!handle) {
        cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }
    
    // load the symbol
    cout << "Loading symbol hello...\n";
    typedef void (*hello_t)();
    hello_t hello = (hello_t) dlsym(handle, "hello");
    if (!hello) {
        cerr << "Cannot load symbol 'hello': " << dlerror() <<
            '\n';
        dlclose(handle);
        return 1;
    }
    
    // use it to do the calculation
    cout << "Calling hello...\n";
    hello();
    
    // close the library
    cout << "Closing library...\n";
    dlclose(handle);
}
