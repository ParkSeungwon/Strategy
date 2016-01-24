#pragma once
#include <gtkmm.h>
#include "darea.h"
#include "../time.h"

class Win : public Gtk::Window
{
public:
	Win();	
	Terrain_data terrain_data;

protected:
    Gtk::Button bt1, bt2, bt3;
    void on_button_click();
    void on_cancel_click();
	void on_open_click();
	bool on_button_press_event(GdkEventButton* e);
	bool on_key_press_event(GdkEventKey* e);
	int label_change(int x, int y, int b);
    Gtk::Box box1;
	Gtk::Box box2;
    Gtk::ScrolledWindow swin;
    Darea area;
	Gtk::Label label1;

private:
	int i_ = 0;
	float f_ = 0;
};

