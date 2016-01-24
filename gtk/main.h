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
	bool on_button_press_event(GdkEventButton* e);
	bool on_key_press_event(GdkEventKey* e);
	int label_change(int x, int y, int button);
    Gtk::Box box1;
	Gtk::Box box2;
    Gtk::ScrolledWindow swin;
    Darea area;
	Gtk::Label label1;

private:
	int i_ = 0;
	float f_ = 0;
};

