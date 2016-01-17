#include <cairomm/context.h>
#include "gtkmain.hpp"

GtkMain::GtkMain()
{
	add(hbox1);
	vbox1.pack_start(menu, Gtk::PACK_SHRINK);
	vbox1.pack_start(hbox1);
	hbox1.pack_start(scrolled_win);
	scrolled_win.add(area);
	hbox1.pack_start(vbox2, Gtk::PACK_SHRINK);
	show_all_children();
}

bool Draw_Area::on_draw()
{
	Gtk::Allocation allocation = get_allocation();
	context->set_line_width(0.05);
	context->move_to(0,0);
	context->line_to(100,100);
	context->stroke();
	return true;
}

Draw_Area::Draw_Area() 
{
	context = get_window()->create_cairo_context();
}

Draw_Area::~Draw_Area() {}
