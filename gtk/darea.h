#pragma once
#include <unordered_map>
#include <gtkmm.h>
#include <memory>
class Terrain_data;

class Darea : public Gtk::DrawingArea
{
public:
	Darea();
	Terrain_data open_map_file(std::string map);
	virtual ~Darea() {}
	void paste_pix(int x, int y, std::string name, float heading = 0);
	void clear_map();
	void refresh();
	void insert_to_draw(int x, int y, int rmin, int rmax, float angle_from, 
			float angle_to, double r, double g, double b, double a);
	int get_height() {return height;}

protected:
	struct To_draw {
		int x, y, rmin, rmax;
		float angle_from, angle_to;
		double color[4];
	};
	struct bk_pixbuf {
		int x, y, w, h;
	};
	int width, height;
	std::vector<To_draw> to_draws;
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	Glib::RefPtr<Gdk::Pixbuf> map;
	std::unordered_map<std::string, Glib::RefPtr<Gdk::Pixbuf>> unit_png;
//	Cairo::RefPtr<Cairo::Context> context;
	static Glib::RefPtr<Gdk::Pixbuf> rotate_pix_buf(
			const Glib::RefPtr<Gdk::Pixbuf> pb, float radian);

private:
	static void rotate(float& x, float& y, float rad);
	static void get_new_dimension(int& w, int& h, float rad);
	Glib::RefPtr<Gdk::Pixbuf> map_backup_;
	std::vector<bk_pixbuf> backgrounds;
};


