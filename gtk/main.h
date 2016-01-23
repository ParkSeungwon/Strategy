#pragma once
#include <gtkmm.h>
#include "darea.h"

class Win : public Gtk::Window
{
public:
	Win();	

protected:
    Gtk::Button bt1, bt2;
    void on_button_click();
    void on_cancel_click();
    Gtk::Box box1;
	Gtk::Box box2;
    Gtk::ScrolledWindow swin;
    Darea area;

private:
	int i_ = 0;
	float f_ = 0;
};

