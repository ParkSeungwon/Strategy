#pragma once
#include <string>
#include <gtkmm.h>
#include "darea.h"
#include "../time.h"
<<<<<<< HEAD

=======
>>>>>>> rerere
class Win : public Gtk::Window
{
public:
	Win();	
	Terrain_data terrain_data;

protected:
<<<<<<< HEAD
    Gtk::Button bt1, bt2, bt3;
=======
    Darea area;
	Time time;
//	Control control;
    Gtk::Button bt1, bt2, bt3;
	void open_terrain_file(std::string filename);
>>>>>>> rerere
    void on_button_click();
    void on_cancel_click();
	void on_open_click();
	bool on_button_press_event(GdkEventButton* e);
	bool on_key_press_event(GdkEventKey* e);
	int label_change(int x, int y, int button);
    Gtk::Box box1;
	Gtk::Box box2;
    Gtk::ScrolledWindow swin;
	Gtk::Label label1;

private:
	int i_ = 0;
	float f_ = 0;
};

