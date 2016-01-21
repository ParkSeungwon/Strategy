#pragma once
#include <gtkmm/drawingarea.h>
#include <unordered_map>
#include <gtkmm.h>

class Darea : public Gtk::DrawingArea
{
public:
	Darea(std::string map, std::string terrain, const std::vector<std::string>& l);
	virtual ~Darea() {}
	int width, height;
	void paste_pix(int x, int y, std::string name, float heading);

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	Glib::RefPtr<Gdk::Pixbuf> map, terrain;
	std::unordered_map<std::string, Glib::RefPtr<Gdk::Pixbuf>> unit_png;
	Cairo::RefPtr<Cairo::Context> context;
	static Glib::RefPtr<Gdk::Pixbuf> rotate_pix_buf(const Glib::RefPtr<Gdk::Pixbuf> pb, float radian);

private:
	static void xy_to_polar(float& x, float& y);
	static void polar_to_xy(float& x, float& y);
};

class Win : public Gtk::Window
{
public:
    Win();

protected:
    Gtk::Button bt1, bt2;
    void on_button_clicked();
    Gtk::Box box1;
	Gtk::Box box2;
    Gtk::ScrolledWindow swin;
    Darea area;
};

