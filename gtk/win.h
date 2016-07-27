#pragma once
#include <string>
#include <gtkmm.h>
#include "darea.h"
#include "Time.h"
#include "terrain_data.h"
#include "interface.h"
class TeamSetup;
class ConnectPopup;

class Win : public Gtk::Window, public Interface
{
public:
	Win();	
	Terrain_data terrain_data;
	void set_user(std::string user);

protected:
    Darea area;
	Time time;
//	Control control;
    Gtk::Button bt1, bt2, bt3, bt4;
	void open_terrain_file(std::string filename);
    void on_button_click();
    void on_cancel_click();
	void on_open_click();
	void on_connect_click();
	bool on_button_press_event(GdkEventButton* e);
	bool on_key_press_event(GdkEventKey* e);
	int label_change(int x, int y, int button);
    Gtk::Box box1;
	Gtk::Box box2;
    Gtk::ScrolledWindow swin;
	Gtk::Label label1;

	std::shared_ptr<TeamSetup> teamsetup;
	std::shared_ptr<ConnectPopup> connectpopup;

private:
	int i_ = 0;
	float f_ = 0;
	std::string user;
};

