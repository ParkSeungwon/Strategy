#include <gtkmm/main.h>
#include "gtkmain.hpp"
#include "main.hpp"

int main(int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	GtkMain form;
	Gtk::Main::run(form);
    return 0;
}
