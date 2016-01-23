#include <gdkmm/pixbuf.h>
#include <iostream>
#include <cmath>
#include "basic.h"
//#include <gdk-pixbuf/gdk-pixbuf.h>
using namespace std;
using namespace Gtk;


Darea::Darea(string mp, string tr, const vector<string>& l) 
{
	add_events(Gdk::BUTTON_PRESS_MASK);
    map = Gdk::Pixbuf::create_from_file(mp);
	map_backup_ = map->copy();
    terrain = Gdk::Pixbuf::create_from_file(tr);

	for(auto& a : l) {
		unit_png.insert({a, Gdk::Pixbuf::create_from_file(a)});
	}
    width = map->get_width();
    height = map->get_height();
	set_size_request(width, height);
//	paste_pix(500, 1500, "bomber_hb.png", 1);
//	paste_pix(500, 1900, "bomber_hb.png", M_PI);
//	paste_pix(500, 1700, "car.png", M_PI/4);
}

bool Darea::on_button_press_event(GdkEventButton* e)
{
	cout << "x " << e->x << endl;
	cout << "y " << e->y << endl;
	if(pfunc != nullptr) pfunc(e->x, e->y);
}

void Darea::clear_map()
{
	for(auto& a : backgrounds) {
		map_backup_->copy_area(a.x, a.y, a.w, a.h, map, a.x, a.y);
	}
	backgrounds.clear();
}

void Darea::paste_pix(int x, int y, string fl, float heading)
{
	auto it = unit_png.find(fl);
	if(it != unit_png.end()) {
		Glib::RefPtr<Gdk::Pixbuf> pix;
		if(heading != 0) pix = rotate_pix_buf(it->second, heading);
		else pix = it->second;
		int w = pix->get_width();
		int h = pix->get_height();
		x -= w/2;
		y = height - y;//change coordinate
		y -= h/2;
		int xof= 0, yof= 0;
		if(x < 0) xof = x;
		if(y < 0) yof = y;

		bk_pixbuf bk;
		bk.x = x - xof;
		bk.y = y - yof;
		bk.w = w + xof;
		bk.h = h + yof;
		backgrounds.push_back(bk);
		pix->composite(map, x - xof, y - yof, w + xof, h + yof, x + xof, y + yof,
			   	1, 1, Gdk::INTERP_NEAREST, 255);
	}
}

void Darea::get_new_dimension(int& w, int& h, float rad)
{
	float fw1 = w /2;
	float fh1 = h /2;
	rotate(fw1, fh1, rad);
	float fw2 = w/2;
	float fh2 = -h/2;
	rotate(fw2, fh2, rad);
	fw1 = abs(fw1) * 2;
	fh1 = abs(fh1) * 2;
	fw2 = abs(fw2) * 2;
	fh2 = abs(fh2) * 2;
	w = fw1 > fw2 ? fw1 : fw2;
	h = fh1 > fh2 ? fh1 : fh2;
}


Glib::RefPtr<Gdk::Pixbuf> Darea::rotate_pix_buf(const Glib::RefPtr<Gdk::Pixbuf> pb, float rad)
{
	int w = pb->get_width();
	int h = pb->get_height();
	auto a = pb->get_has_alpha();
	auto b = pb->get_bits_per_sample();
	auto c = pb->get_colorspace();
	auto r = pb->get_rowstride();
	auto n = pb->get_n_channels();
	auto p = pb->get_pixels();

	int qw = w;
	int qh = h;
	get_new_dimension(qw, qh, rad);
	auto q = Gdk::Pixbuf::create(c, a, b, qw, qh);
	q->fill(0);
	auto rq = q->get_rowstride();
	auto nq = q->get_n_channels();
	auto pq = q->get_pixels();

	auto fp = [=] (int x, int y) {return p + y * r + x * n;};
	auto fq = [=] (int x, int y) {return pq + y * rq + x * nq;};

	unsigned char *pp, *qq;
	float xx, yy;
   	for(int x = 0; x < qw; x++) {
		for(int y = 0; y < qh; y++) {
			xx = x + 0.5;
			yy = y + 0.5;
			yy = qh - yy;
			xx -= qw/2;
			yy -= qh/2;
			rotate(xx, yy, -rad);
			xx += w/2 ;
			yy += h/2;
			yy = h - yy;
			if(xx < w && xx >=0 && yy < h && yy >=0) {
				qq = fq(x, y);
				pp = fp(xx, yy);
				for(int i=0; i<4; i++) qq[i] = pp[i];
			}
		}
	}
	return q;
}

void Darea::xy_to_polar(float& x, float& y)
{
	float r = sqrt(x*x + y*y);
	if(x == 0) {
		x = r;
		if(y > 0) y = M_PI / 2;
		else y = -M_PI / 2;
	} else {
		float theta = atan(y/x);
		if(x < 0) theta += M_PI;
		x = r;
		y = theta;
	}
}

void Darea::polar_to_xy(float& r, float& theta)
{
	float x = r * cos(theta);
	float y = r * sin(theta);
	r = x;
	theta = y;
}

void Darea::rotate(float& x, float& y, float rad)
{
	xy_to_polar(x, y);
	y += rad;
	polar_to_xy(x, y);
}

bool Darea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
//    car->composite(map, 0, 0, car->get_width() -100, car->get_height()-100, -100, -100, 1, 1, Gdk::INTERP_NEAREST, 255);//255는 전경이 완전한 불투명. 0은 완전 투명. 알파는 투과. 오프셋과 데스트의 좌표를 같이 해야함.
  //  airplane->composite(map, 300, 300, airplane->get_width(), airplane->get_height(), 300, 300, 1, 1, Gdk::INTERP_NEAREST, 255);//255는 전경이 완전한 불투명. 0은 완전 투명. 알파는 투과. 오프셋과 데스트의 좌표를 같이 해야함.
	Gdk::Cairo::set_source_pixbuf(cr, map, 0, 0);
    cr->paint();
    cr->set_line_width(10.0);
	for(auto& a : to_draws) {
		cr->set_source_rgba(a.color[0], a.color[1], a.color[2], a.color[3]);
		cr->arc(a.x, a.y, a.rmin, a.angle_from, a.angle_to);
		cr->arc_negative(a.x, a.y, a.rmax, a.angle_to, a.angle_from);
		cr->close_path();
		cr->fill_preserve();
		cr->stroke();
	}
    return true;
}

void Darea::refresh()
{
	auto win = get_window();
    if (win)  {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
}

Win::Win() :
   	bt1("OK"), bt2("cancel"), box2(ORIENTATION_VERTICAL), 
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
 //   cout << "높이 " << area.height << endl;
 //   area.set_size_request(area.width, area.height);
    box1.pack_start(area);
    bt1.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_button_click));
    bt2.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_cancel_click));
    show_all_children();
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

To_draw::To_draw(int x, int y, int rmin, int rmax, float af, float at, double r, double g, double b, double a)
{
	this->x = x;
	this->y = y;
	this->rmin = rmin;
	this->rmax = rmax;
	angle_from = af;
	angle_to = at;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void Win::on_cancel_click()
{
	auto cr = area.get_window()->create_cairo_context(); 
 // draw red lines out from the center of the window
    cr->set_source_rgba(0.0, 0.0, 0.8, 0.3);
    //cr->translate(x, y);
    //cr->scale(900 / 2.0, 800 / 2.0);
    cr->arc(300, 300, 0, 0.0, M_PI);
	cr->arc_negative(300, 300, 200, M_PI, 0);
	cr->close_path();
	cr->fill_preserve();
    cr->stroke();
	To_draw d(300, 300, 0, 100, 0, M_PI/2, 0.0, 0.4, 0.0, 0.2);
	area.to_draws.push_back(d);
	d.x = 300;
	d.y = 300;
	d.rmin = 0;
	d.rmax = 100;
	d.angle_from = 0;
	d.angle_to = M_PI/2;
	d.color[0] = 0; 
	d.color[1] = 0.4;
	d.color[2] = 0;
	d.color[3] = 0.2;
	area.to_draws.push_back(d);
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


