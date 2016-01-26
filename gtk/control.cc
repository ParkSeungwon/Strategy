#include "control.h"

Control::Control(Darea& ar, Time& t)
{
	darea = &ar;
	time = &t;
}

Control::sync()
{
	int x, y, al, tm, rc, min, max;
	float fr, to, hd;
	for(auto& a : time->deployedUnits) {
		if(a.known_to[user.ally]) {
			x = a.x; 
			y = a.y;
			hd = a.get_headingToward();
			al = a.get_ally();
			tm = a.get_team();
			rc = a.get_intelligenceRadius();
			darea->paste_pix(x, y, a.unit_name, hd);
			darea->insert_to_draw(x, y, rc, rc, 0, 2 * M_PI, color[tm][0],
					color[tm][1], color[tm][2], color[tm][3]);
			for(auto& w : a) {
				min = w.get_shootingRangeMin();
				max = w.get_shootingRangeMax();
				fr = w.get_shootingAngleFrom();
				to = w.get_shootingAngleTo();
				darea->insert_to_draw(x, y, min, max, hd + fr, hd + to, 
						color[tm][0], color[tm][1], color[tm][2], color[tm][3]);
			}
		}
	}
}		

Terrain_data Darea::return_terrain_data()
{
	Terrain_data td;
	td.w = terrain->get_width();
	td.h = terrain->get_height();
	int r = terrain->get_rowstride();
	int n = terrain->get_n_channels();
	unsigned char* p = terrain->get_pixels();
	unsigned char* q;
	td.tmap = new size_t[td.h * td.w];
	size_t tmp, dot;
	for(int y=0; y<td.h; y++) {
		for(int x=0; x<td.w; x++) {
			q = p + y * r + x * n;
			tmp = q[0];
		   	tmp << 24;
			dot = tmp;
			tmp = q[1];
			tmp << 16;
			dot |= tmp;
			tmp = q[2];
			tmp << 8;
			dot |= tmp;
			tmp = q[3];
			dot |= tmp;
			td.tmap[y*td.w + x] = dot; 
		}
	}
	return td;
}

Terrain_data::Terrain_data(Terrain_data&& tr)
{
	w = tr.w;
	h = tr.h;
	tmap = tr.tmap;
	tr.tmap = nullptr;
}

Terrain_data& Terrain_data::operator=(Terrain_data&& tr)
{
	w = tr.w;
	h = tr.h;
	tmap = tr.tmap;
	tr.tmap = nullptr;
	return *this;
}

Terrain_data::~Terrain_data()
{
	if(tmap != nullptr) delete [] tmap;
}

