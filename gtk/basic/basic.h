#pragma once
#include <unordered_map>
#include <gtkmm.h>

struct bk_pixbuf {
	int x, y, w, h;
};

struct To_draw {
	int x, y, rmin, rmax;
	float angle_from, angle_to;
	char color[4];
};

class Darea : public Gtk::DrawingArea
{
public:
	Darea(std::string map, std::string terrain, const std::vector<std::string>& l);
	virtual ~Darea() {}
	void paste_pix(int x, int y, std::string name, float heading = 0);
	void clear_map();
	void refresh();
	std::vector<To_draw> to_draws;
	int (*pfunc)(int x, int y) = nullptr;

protected:
	int width, height;
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	bool on_button_press_event(GdkEventButton *event);
	Glib::RefPtr<Gdk::Pixbuf> map, terrain;
	std::unordered_map<std::string, Glib::RefPtr<Gdk::Pixbuf>> unit_png;
	Cairo::RefPtr<Cairo::Context> context;
	static Glib::RefPtr<Gdk::Pixbuf> rotate_pix_buf(
			const Glib::RefPtr<Gdk::Pixbuf> pb, float radian);

private:
	static void xy_to_polar(float& x, float& y);
	static void polar_to_xy(float& x, float& y);
	static void rotate(float& x, float& y, float rad);
	static void get_new_dimension(int& w, int& h, float rad);
	Glib::RefPtr<Gdk::Pixbuf> map_backup_;
	std::vector<bk_pixbuf> backgrounds;
};

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

