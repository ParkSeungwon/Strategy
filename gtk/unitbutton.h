#pragma once
#include<gtkmm.h>
class UnitButton : public Gtk::Button
{
public:
	UnitButton(std::string nation, std::string unitname);

protected:
	Gtk::Image img;
};	

class Produce : public Gtk::Dialog
{
public:
};
