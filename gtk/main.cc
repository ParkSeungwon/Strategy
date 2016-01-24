#include <string>
#include <iostream>
#include "main.h"
using namespace Gtk;
using namespace std;

Win::Win() :
   	bt1("OK"), bt2("cancel"), box2(ORIENTATION_VERTICAL), label1("라벨"), 
	area("europe.png", "europe.png", {"bomber_hb.png", "car.png"}) 
{
    set_border_width(10);
    set_default_size(900, 900);
    add(box1);
    swin.add(area);
    swin.set_policy(Gtk::POLICY_ALWAYS, POLICY_ALWAYS);
	box1.pack_start(box2, PACK_SHRINK);
	box1.pack_start(swin);
    box2.pack_start(bt1, PACK_SHRINK);
    box2.pack_start(bt2, PACK_SHRINK);
	box2.pack_start(label1, PACK_SHRINK);
 //   cout << "높이 " << area.height << endl;
 //   area.set_size_request(area.width, area.height);
    box1.pack_start(area);
    bt1.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_button_click));
    bt2.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_cancel_click));
    show_all_children();
}

bool Win::on_button_press_event(GdkEventButton* e)
{
	label_change(e->x, e->y, e->button);
}

bool Win::on_key_press_event(GdkEventKey* e)
{
	cout << "key : " << e->keyval << endl;
	return false;
}

int Win::label_change(int x, int y, int b)
{
	string s;
	s = to_string(x);
	s += "\n" + to_string(y);
	s += "\n" + to_string(b);
	label1.set_text(s);
	return s.size();
}

void Win::on_button_click()
{
	area.clear_map();
	area.paste_pix(100 + i_++, 1900, "bomber_hb.png", 1 + f_++);
	area.paste_pix(500, 1900, "bomber_hb.png", M_PI);
	area.paste_pix(500, 1700, "car.png", M_PI/4);
    // force our program to redraw the entire clock.
	area.refresh();
}


void Win::on_cancel_click()
{
//	auto cr = area.get_window()->create_cairo_context(); 
// // draw red lines out from the center of the window
//    cr->set_source_rgba(0.0, 0.0, 0.8, 0.3);
//    //cr->translate(x, y);
//    //cr->scale(900 / 2.0, 800 / 2.0);
//    cr->arc(300, 300, 0, 0.0, M_PI);
//	cr->arc_negative(300, 300, 200, M_PI, 0);
//	cr->close_path();
//	cr->fill_preserve();
//    cr->stroke();
//	To_draw d(300, 300, 0, 100, 0, M_PI/2, 0.0, 0.4, 0.0, 0.2);
//	area.to_draws.push_back(d);
//	d.x = 300;
//	d.y = 300;
//	d.rmin = 0;
//	d.rmax = 100;
//	d.angle_from = 0;
//	d.angle_to = M_PI/2;
//	d.color[0] = 0; 
//	d.color[1] = 0.4;
//	d.color[2] = 0;
//	d.color[3] = 0.2;
//	area.to_draws.push_back(d);
	area.to_draws.push_back(To_draw(300 + i_++*10, 300, 100, 100, 0, M_PI/2, 
				(i_%10)/10.0, 0.4, 0.0, 0.2));
	area.refresh();
//    cr->restore();
}

int main(int argc, char** argv)
{
    auto app = Application::create(argc, argv, "");

    Win win;
    return app->run(win);
}


