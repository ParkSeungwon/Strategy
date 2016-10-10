#pragma once
#include <unordered_map>
#include <gtkmm.h>
#include <memory>
#include "src/Util.h"//Glob::To_draw
#include"interface.h"
class Terrain_data;

class Darea : public Gtk::DrawingArea, public FieldInterface
{
public:
	Darea();
	Terrain_data open_map_file(std::string map);
	virtual ~Darea() {}
	void paste_pix(int x, int y, std::string name, float heading = 0);
	void clear_map();
	void refresh();
	void insert_to_draw(Glob::To_draw& td);
	int get_height() {return height;}
	static Gtk::Image get_icon(std::string nation, std::string unitName);

protected:
	struct bk_pixbuf {
		int x, y, w, h;
	};
	int width, height;
	std::vector<Glob::To_draw> to_draws;
	static std::unordered_map<std::string, Glib::RefPtr<Gdk::Pixbuf>> unit_png;
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	Glib::RefPtr<Gdk::Pixbuf> map;
//	Cairo::RefPtr<Cairo::Context> context;
	static Glib::RefPtr<Gdk::Pixbuf> rotate_pix_buf(
			const Glib::RefPtr<Gdk::Pixbuf> pb, float radian);

private:
	static void rotate(float& x, float& y, float rad);
	static void get_new_dimension(int& w, int& h, float rad);
	Glib::RefPtr<Gdk::Pixbuf> map_backup_;
	std::vector<bk_pixbuf> backgrounds;
};


