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


