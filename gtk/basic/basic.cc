#include <gtkmm.h>
#include <gdkmm/pixbuf.h>
#include <iostream>
using namespace std;

class Darea : public Gtk::DrawingArea
{
public:
	Darea();
	virtual ~Darea() {}

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	Glib::RefPtr<Gdk::Pixbuf> image;
};

class Win : public Gtk::Window
{
public:
	Win();

protected:
	Gtk::Button bt1, bt2;
	void on_button_clicked();
	Gtk::Box box1;
	Gtk::ScrolledWindow swin;
	Darea area;
};

Darea::Darea()
{
	image = Gdk::Pixbuf::create_from_file("europe.png");
}

bool Darea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	auto a = get_allocation();
	const int w = a.get_width();
	const int h = a.get_height();
	Gdk::Cairo::set_source_pixbuf(cr, image, 0, 0);//(w - image->get_width())/2, (h - image->get_height())/2);
	cr->paint();
	return true;
}

Win::Win() : bt1("OK"), bt2("cancel") {
	add(swin);
	swin.add(box1);
	swin.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
//	box1.pack_start(bt1);
//	box1.pack_start(bt2);
	box1.pack_start(area);
	bt1.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_button_clicked));
	bt2.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_button_clicked));
	show_all_children();
}

void Win::on_button_clicked()
{
	cout << "Hello" << endl;
}

int main(int argc, char** argv)
{
	auto app = Gtk::Application::create(argc, argv, "");

	Win win;
	return app->run(win);
}


