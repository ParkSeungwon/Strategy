#pragma once
#include <unordered_map>
#include <gtkmm.h>
#include <memory>

struct bk_pixbuf {
	int x, y, w, h;
};

struct To_draw {
	To_draw(int x, int y, int rmin, int rmax, float angle_from, float angle_to, 
			double r, double g, double b, double a);
	int x, y, rmin, rmax;
	float angle_from, angle_to;
	double color[4];
};

class Terrain_data 
{
public:
	virtual ~Terrain_data();
	Terrain_data() {}
	Terrain_data(Terrain_data&& tr);
	Terrain_data& operator=(Terrain_data&& tr);
	int w, h;
	size_t *tmap = nullptr;
};

class Darea : public Gtk::DrawingArea
{
public:
	Darea();
	int open_map_file(std::string map, std::string terrain);
	virtual ~Darea() {}
	void paste_pix(int x, int y, std::string name, float heading = 0);
	void clear_map();
	void refresh();
	std::vector<To_draw> to_draws;
	Terrain_data return_terrain_data();

protected:
	int width, height;
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	//bool on_button_press_event(GdkEventButton *event);
	//bool on_key_press_event(GdkEventKey* kevent);
	Glib::RefPtr<Gdk::Pixbuf> map, terrain;
	std::unordered_map<std::string, Glib::RefPtr<Gdk::Pixbuf>> unit_png;
	Cairo::RefPtr<Cairo::Context> context;
	static Glib::RefPtr<Gdk::Pixbuf> rotate_pix_buf(
			const Glib::RefPtr<Gdk::Pixbuf> pb, float radian);

private:
	static void rotate(float& x, float& y, float rad);
	static void get_new_dimension(int& w, int& h, float rad);
	Glib::RefPtr<Gdk::Pixbuf> map_backup_;
	std::vector<bk_pixbuf> backgrounds;
};


