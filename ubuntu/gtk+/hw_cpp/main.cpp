extern "C" void gtk_init(int* argc,  char* *argv[]);
extern "C" long* gtk_window_new(long);
extern "C" long* gtk_button_new_with_label(char*);
extern "C" void gtk_widget_show(long*);
extern "C" void gtk_container_add(long*, long*);
extern "C" void g_signal_connect_object(long*, char*, void(long *, void*), void*);
extern "C" void g_signal_connect_data(long*, char*, void(long *, void*), void*, void*, void*);
extern "C" void gtk_main();
extern "C" void gtk_main_quit();

#include <iostream>
using namespace std;
void destroy(long *widget, void* data) {	
	gtk_main_quit();
}

void listener(long *widget, void* data) {
	cout << "Hello, world!" << (char*)data << '\n';
}

int main( int   argc,  char *argv[] ) {
	long *window;   
	long *btn;
    gtk_init (&argc, &argv);    
    window = gtk_window_new(0);
    g_signal_connect_object(window, "destroy", destroy, 0);
    btn = gtk_button_new_with_label("Console print"); 
    gtk_container_add(window, btn);
    gtk_widget_show(btn);
    gtk_widget_show(window);
    g_signal_connect_data(btn, "clicked", listener, (void*)"bee", 0, 0);    
    gtk_main ();/**/
	return 0;
}
//g++ main.o -L. lgtk-x11-2.0 -o cpp2
