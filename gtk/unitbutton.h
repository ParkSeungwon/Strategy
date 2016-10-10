#pragma once
#include<gtkmm.h>
#include<vector>
class City;
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
	Produce(const City& city);
	std::string selection;

protected:
	std::vector<UnitButton> icons;
	void on_click(std::string s);
};
