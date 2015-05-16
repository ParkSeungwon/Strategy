#include <iostream>
using namespace std;
#include <gtkmm.h>
#include "gtkmap.h"

int test();

int main (int argc, char* argv[])
{
	Gtk::Main kit(argc, argv);
	Gtk::Window win;
	GtkMap gmap;
	win.add(gmap);
	gmap.show();
	
	Gtk::Main::run(win);
	
	return 0;
}
