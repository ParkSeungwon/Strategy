#include "gtkmain.hpp"

GtkMain::GtkMain()
{
	//context = area.get_window()->create_cairo_context();
	add(hbox1);
	//vbox1.pack_start(menu, Gtk::PACK_SHRINK);
	//vbox1.pack_start(hbox1);
	//hbox1.pack_start(area);
	//hbox1.pack_start(vbox2, Gtk::PACK_SHRINK);
	show_all_children();
}
