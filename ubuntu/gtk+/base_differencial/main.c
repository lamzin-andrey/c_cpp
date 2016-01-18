extern void gtk_init(int* argc,  char* *argv[]);
extern long* gtk_window_new(long);
extern void gtk_widget_show(long*);
extern void gtk_main();

int main( int   argc,  char *argv[] ) {
	long *window;    
    gtk_init (&argc, &argv);    
    window = gtk_window_new (0/*GTK_WINDOW_TOPLEVEL*/);
    gtk_widget_show  (window);    
    gtk_main ();
	return 0;
}
//ubuntu 11.04^  gcc main.o -L. -lgtk-x11-2.0 -o yourapp
//ubuntu 12.04 liveCD:
/*
ubuntu@ubuntu:~$ gcc main.o -L. /usr/lib/i386-linux-gnu/libgtk-x11-2.0.so.0.2400.10 -o yourapp
gcc main.o -L. /usr/lib/i386-linux-gnu/libgtk-x11-2.0.so.0 -o yourapp
*/

