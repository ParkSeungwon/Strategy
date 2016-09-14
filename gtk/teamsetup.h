#pragma once
#include <gtkmm.h>

class TeamSetup : public Gtk::Dialog
{
public:
	TeamSetup(int c);
	virtual ~TeamSetup();
	Gtk::ComboBoxText* comboboxes;
	
protected:
	Gtk::HBox* hboxes;
	void on_click();
};


