#pragma once
#include <gtkmm.h>

class GtkMain : public Gtk::Window
{
public:
	GtkMain();

protected:
	//Gtk::MenuBar menu;
	//Gtk::VBox vbox1, vbox2;
	Gtk::HBox hbox1;
	//Gtk::DrawingArea area;
	//Cairo::RefPtr<Cairo::Context> context;

private:
};
