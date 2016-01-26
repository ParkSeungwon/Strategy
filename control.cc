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


