#include <gdkmm/pixbuf.h>
#include <iostream>
#include <cmath>
#include <complex>
#include "darea.h"
#include "../file.h"
#include "../terrain_data.h"
//#include <gdk-pixbuf/gdk-pixbuf.h>
using namespace std;
using namespace Gtk;


Darea::Darea() 
{
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::KEY_PRESS_MASK);
    map = Gdk::Pixbuf::create_from_file("car.png");
	
	File f;
	f.find_all_ext("units", ".png");
	for(auto& a : f.file_names) {
		unit_png.insert({a, Gdk::Pixbuf::create_from_file(a)});
		cout << "opening file " << a << endl;
	}
    width = map->get_width();
    height = map->get_height();
	set_size_request(width, height);
}

Terrain_data Darea::open_map_file(string mp)
{
	map = Gdk::Pixbuf::create_from_file(mp);
	map_backup_ = map->copy();
    width = map->get_width();
    height = map->get_height();
	set_size_request(width, height);
	auto ppp = map->get_pixels();

	//prepare terrain data for model
	mp.replace(mp.size()-3, 3, "ter");
	Glib::RefPtr<Gdk::Pixbuf> ter = map->copy();//Gdk::Pixbuf::create_from_file(mp);
	if(ter->get_width() != width || ter->get_height() != height) throw 3;
	auto r = ter->get_rowstride();
	auto n = ter->get_n_channels();
	auto p = ter->get_pixels();

	auto fp = [r, n, p] (int x, int y) {return p + y * r + x * n;};

	Terrain_data ret(width, height);
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			for(int i=0; i<4; i++) ret.pixel(x, height - y - 1)[i] = fp(x, y)[i];
		}
	}
	
	return ret;
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


void Darea::rotate(float& x, float& y, float rad)
{
	complex<float> a {x, y};
	a *= complex<float> {cos(rad), sin(rad)};
	x = a.real();
	y = a.imag();
}

bool Darea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
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

void Darea::insert_to_draw(int x, int y, int rmin, int rmax, float af, float at, double r, double g, double b, double a)
{
	To_draw t;
	t.x = x;
	t.y = y;
	t.rmin = rmin;
	t.rmax = rmax;
	t.angle_from = af;
	t.angle_to = at;
	t.color[0] = r;
	t.color[1] = g;
	t.color[2] = b;
	t.color[3] = a;
	to_draws.push_back(t);
}


