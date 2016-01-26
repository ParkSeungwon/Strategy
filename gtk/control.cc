#include "control.h"
#include "../time.h"
#include "../Unit.h"
#include "../Weapon.h"
#include "darea.h"
#include "main.h"

Control::Control(Win& w, User& u)
{
	win = &w;
	user = u;
	area = &w.area;
	time = new Time(w.terrain_data.width, w.terrain_data.height, w.terrain_data.tmap, u.ally);
}

void Control::sync()
{
	int x, y, al, tm, rc, min, max;
	float fr, to, hd;
	for(auto& a : time->deployedUnits) {
		if(a->get_known_to(user.ally)) {
			x = a->x; 
			y = a->y;
			hd = a->heading_toward;
			al = a->get_ally();
			tm = a->get_team();
			rc = a->get_intelligenceRadius();
			area->paste_pix(x, y, a->unit_name(), hd);
			area->insert_to_draw(x, y, rc, rc, 0, 2 * M_PI, color[tm][0],
					color[tm][1], color[tm][2], color[tm][3]);
			for(auto& w : a->weapon) {
				min = w.get_shootingRangeMin();
				max = w.get_shootingRangeMax();
				fr = w.get_shootingAngleFrom();
				to = w.get_shootingAngleTo();
				area->insert_to_draw(x, y, min, max, hd + fr, hd + to, 
						color[tm][0], color[tm][1], color[tm][2], color[tm][3]);
			}
		}
	}
}		


