#include <gtkmm/drawingarea.h>

class Darea : public Gtk::DrawingArea
{
public:
	Darea();
	virtual ~Darea() {}
	int width, height;
	load_map(std::string file);

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	Glib::RefPtr<Gdk::Pixbuf> map, terrain;
	std::unordered_map<std::string, Glib::RefPtr<Gdk::Pixbuf>> unit_png;
	Cairo::RefPtr<Cairo::Context> context;

