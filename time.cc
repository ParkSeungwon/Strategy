#include <algorithm>
#include "time.h"
#include "Unit.h"
#include <vector>

void Time::time_pass(int time)
{
	//change position
	for(auto& u : deployedUnits) {
		u.time_pass(time);
	}
	//attck
	for(auto& u : deployedUnits) {
		for(auto& w : u.weapon) {
			w.adjust_range_clip(u);
			u >> deployedUnits;
		}
	}
	//remove destroyed units
	std::vector<Unit>::iterator it;
	it = deployedUnits.begin();
	while(it != deployedUnits.end()) {
		it = find(it, deployedUnits.end(), 0);//find health <=0
//		deployedUnits.erase(it);
	}

	generate_recon_bitmap();
	generate_weapon_range_bitmap();
}

