#include <gdkmm/pixbuf.h>
#include <iostream>
#include <cmath>
#include "basic.h"
//#include <gdk-pixbuf/gdk-pixbuf.h>
using namespace std;
using namespace Gtk;


Darea::Darea(string mp, string tr, const vector<string>& l) 
{
    map = Gdk::Pixbuf::create_from_file(mp);
    terrain = Gdk::Pixbuf::create_from_file(tr);

	for(auto& a : l) {
		unit_png.insert({a, Gdk::Pixbuf::create_from_file(a)});
	}
    width = map->get_width();
    height = map->get_height();
	set_size_request(width, height);
}

void Darea::paste_pix(int x, int y, string fl, float heading)
{
	auto it = unit_png.find(fl);
	if(it != unit_png.end()) {
		auto pix = it->second;
		if(heading != 0) pix = rotate_pix_buf(it->second, heading);
		int w = pix->get_width();
		int h = pix->get_height();
		x -= w/2;
		y = height - y;//change coordinate
		y -= h/2;
		int xof= 0, yof= 0;
		if(x < 0) xof = x;
		if(y < 0) yof = y;
		pix->composite(map, x - xof, y - yof, w + xof, h + yof, x + xof, y + yof,
			   	1, 1, Gdk::INTERP_NEAREST, 255);
	}
}

Glib::RefPtr<Gdk::Pixbuf> Darea::rotate_pix_buf(const Glib::RefPtr<Gdk::Pixbuf> pb, float rad)
{
	int w = pb->get_width();
   	int qw = w * 1.414;
	int h = pb->get_height();
   	int qh = h * 1.414;
	auto a = pb->get_has_alpha();
	auto b = pb->get_bits_per_sample();
	auto c = pb->get_colorspace();
	auto r = pb->get_rowstride();
	auto n = pb->get_n_channels();
	auto p = pb->get_pixels();

	auto q = Gdk::Pixbuf::create(c, a, b, qw, qh);
	auto rq = q->get_rowstride();
	auto nq = q->get_n_channels();
	auto pq = q->get_pixels();

	auto fp = [=] (int x, int y) {return p + y * r + x * n;};
	auto fq = [=] (int x, int y) {return pq + y * rq + x * nq;};

	unsigned char *pp, *qq;
	float xx, yy;
   	for(int x = 0; x < w; x++) {
		for(int y = 0; y < h; y++) {
			pp = fp(x, y);
			yy = y + 0.5;
			xx = x + 0.5;
			yy = h - yy;
			xx -= w/2;
			yy -= h/2;
			xy_to_polar(xx, yy);//x,y is ref
			yy += rad;
			polar_to_xy(xx, yy);
			xx += qw/2 ;
			yy += qh/2;
			yy = qh - yy;
			qq = fq(xx, yy);
			for(int i=0; i<4; i++) qq[i] = pp[i];
		}
	}
	return q;
}

void Darea::xy_to_polar(float& x, float& y)
{
	float r = sqrt(x*x + y*y);
	float theta = atan(y/x);
	x = r;
	y = theta;
}

void Darea::polar_to_xy(float& r, float& theta)
{
	float x = r * cos(theta);
	float y = r * sin(theta);
	r = x;
	theta = y;
}

bool Darea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
//    car->composite(map, 0, 0, car->get_width() -100, car->get_height()-100, -100, -100, 1, 1, Gdk::INTERP_NEAREST, 255);//255는 전경이 완전한 불투명. 0은 완전 투명. 알파는 투과. 오프셋과 데스트의 좌표를 같이 해야함.
  //  airplane->composite(map, 300, 300, airplane->get_width(), airplane->get_height(), 300, 300, 1, 1, Gdk::INTERP_NEAREST, 255);//255는 전경이 완전한 불투명. 0은 완전 투명. 알파는 투과. 오프셋과 데스트의 좌표를 같이 해야함.
	cr->save();
	paste_pix(500, 1900, "car.png", 2);
	cr->restore();
	Gdk::Cairo::set_source_pixbuf(cr, map, 0, 0);
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

Win::Win() : bt1("OK"), bt2("cancel"), box2(ORIENTATION_VERTICAL), area("europe.png", "europe.png", {"car.png"}) {
    set_border_width(10);
    set_default_size(900, 900);
    add(box1);
    swin.add(area);
    swin.set_policy(Gtk::POLICY_ALWAYS, POLICY_ALWAYS);
	box1.pack_start(box2, PACK_SHRINK);
	box1.pack_start(swin);
    box2.pack_start(bt1, PACK_SHRINK);
    box2.pack_start(bt2, PACK_SHRINK);
    cout << "높이 " << area.height << endl;
 //   area.set_size_request(area.width, area.height);
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
    auto app = Application::create(argc, argv, "");

    Win win;
    return app->run(win);
}


