/*extern void gtk_init(int* argc,  char* *argv[]);
extern long* gtk_window_new(long);
extern void gtk_widget_show(long*);
extern void gtk_main();
extern void g_signal_connect_object(long*, char*, void(*)(long* , long*), void*);
extern void gtk_container_add(long*, long*);
extern void gtk_box_pack_start(long* , long* , int , int , int );
extern void gtk_container_set_border_width(long*, int);
extern long* gtk_button_new_with_label(char*);
extern long* gtk_hbox_new(int , int);
extern long* gtk_vbox_new(int , int);
extern long* gtk_fixed_new();
extern void* gtk_fixed_put(long*, long*, int, int);
/**/


//using namespace std;




void f1() {

}


void hello( long *widget, long*   data ) {	
	
}

int wrap( int   argc,  char *argv[] ) {
	/*
	long *window;
	long *button;
	long *button2;
	long *hbox;
	
    gtk_init (&argc, &argv);    
    window = gtk_window_new (0);
    gtk_container_set_border_width(window, 10);
    hbox = gtk_fixed_new();
    button = gtk_button_new_with_label("Hello World");
   button2 = gtk_button_new_with_label("Hello World1");
    g_signal_connect_object(button, "clicked", hello, 0);
    gtk_container_add(window, hbox);
    gtk_fixed_put(hbox, button, 1,5);
    gtk_fixed_put(hbox, button2, 150,5);
    //gtk_box_pack_start(hbox, button2, 1,1,0);
    gtk_widget_show  (button);    
    gtk_widget_show  (button2);        
    gtk_widget_show  (hbox);    
    gtk_widget_show  (window);    
    gtk_main ();/**/
	return 0;
}
//ubuntu 11.04^  gcc main.o -L. -lgtk-x11-2.0 -o yourapp
//ubuntu 12.04 liveCD:
/*
ubuntu@ubuntu:~$ gcc main.o -L. /usr/lib/i386-linux-gnu/libgtk-x11-2.0.so.0.2400.10 -o yourapp
gcc main.o -L. /usr/lib/i386-linux-gnu/libgtk-x11-2.0.so.0 -o yourapp
*/

