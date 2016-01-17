#pragma once
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/menubar.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/scrolledwindow.h>

class Draw_Area : public Gtk::DrawingArea
{
public:
	Draw_Area();
	virtual ~Draw_Area();

protected:
	virtual bool on_draw();

private:
	Cairo::RefPtr<Cairo::Context> context;
};

class GtkMain : public Gtk::Window
{
public:
	GtkMain();

protected:
	Gtk::MenuBar menu;
	Gtk::VBox vbox1, vbox2;
	Gtk::HBox hbox1;
	Gtk::ScrolledWindow scrolled_win;
	Draw_Area area;

private:
};
