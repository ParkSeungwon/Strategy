#include <gtkmm.h>
#include "gtkmap.h"

bool GtkMap::on_expose_event(GdkEventExpose* event)
{
	Glib::RefPtr<Gdk::Window> window = get_window();
	
	Gtk::Allocation alloc = get_allocation();
	const int width = alloc.get_width();
	const int height = alloc.get_height();
	Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
	cr->scale(width, height);
	double x0=0.1, y0=0.5,
		x1=0.4, y1=0.9,
		x2=0.6, y2=0.1,
		x3=0.9, y3=0.5;
		
	cr->set_line_width(10.0);
	cr->move_to(x0, y0);
	cr->curve_to(x1, y1, x2, y2, x3, y3);
	cr->stroke();
	cr->set_source_rgba(1, 0.2, 0.2, 0.6);
	cr->move_to(x0, y0);
	cr->line_to(x1, y1);
	cr->move_to(x2, y2);
	cr->line_to(x3, y3);
	cr->stroke();
	return true;
}
