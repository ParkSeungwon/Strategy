#include <gtkmm.h>
#include <gdkmm/pixbuf.h>
#include <iostream>
//#include <gdk-pixbuf/gdk-pixbuf.h>
using namespace std;

class Darea : public Gtk::DrawingArea
{
public:
	Darea();
	virtual ~Darea() {}
	int width, height;

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	Glib::RefPtr<Gdk::Pixbuf> image, car;
	Cairo::RefPtr<Cairo::Context> context;
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
	car = Gdk::Pixbuf::create_from_file("car.png");
	width = image->get_width();
	height = image->get_height();
}

bool Darea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	car->composite(image, 100, 100, car->get_width(), car->get_height(), 100, 100, 1, 1, Gdk::INTERP_NEAREST, 255);//255는 전경이 완전한 불투명. 0은 완전 투명. 알파는 투과. 오프셋과 데스트의 좌표를 같이 해야함.
	Gdk::Cairo::set_source_pixbuf(cr, image, 0, 0);
	cr->paint();
	cr->set_line_width(10.0);

	  // draw red lines out from the center of the window
	  cr->set_source_rgb(0.8, 0.0, 0.0);
	  cr->move_to(0, 0);
	  cr->line_to(300, 300);
	  cr->line_to(0, 600);
	  cr->move_to(400, 400);
	  cr->line_to(100, 200);
	  cr->stroke();	
cr->save();
cr->set_source_rgba(0.0, 0.0, 0.8, 0.3);
//cr->translate(x, y);
//cr->scale(900 / 2.0, 800 / 2.0);
cr->arc(300, 300, 100, 0.0, M_PI);
cr->stroke();
cr->restore();
	return true;
}

Win::Win() : bt1("OK"), bt2("cancel") {
	set_border_width(10);
	set_default_size(900, 900);
	add(swin);
	swin.add(box1);
	swin.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
//	box1.pack_start(bt1);
//	box1.pack_start(bt2);
	cout << "높이 " << area.height << endl;
	area.set_size_request(area.width, area.height);
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


