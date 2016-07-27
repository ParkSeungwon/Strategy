#include<gtkmm.h>
#include"darea.h"
#include"../time.h"
#include"../Unit.h"
#include"../Weapon.h"

void Time::sync()
{
	for(auto& u : deployedUnits) {
		battlefield.paste_pix(u->x, u->y, u->get_unitName(), u->heading_toward);
		for(auto& w : u->weapon) {
			battlefield.insert_to_draw({u->x, u->y, w.get_shootingRangeMin(), 
					w.get_shootingRangeMax(), 
					w.get_shootingAngleFrom() + u->heading_toward, 
					w.get_shootingAngleTo() + u->heading_toward, 
					u->get_team() / 8 , 0.3,0.3,0.3});
		}
	}
}
