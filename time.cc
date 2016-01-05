#include "time.h"
#include "Unit.h"
#include <vector>

void Time::time_pass(int time)
{
	//change position
	for(int i=0; i<maxTeam; i++) {
		for(auto& u : deployedUnits[i]) {
			u.time_pass(time);
		}
	}
	//attck
	for(int i=0; i<maxTeam; i++) {
		for(auto& u : deployedUnits[i]) {
			for(auto& w : u.weapon) {
				w.adjust_range_clip(u);
				w >> deployedUnits[!i];
			}
		}
	}
	//remove destroyed units
	std::vector<Unit>::iterator it;
	for(int i=0; i<maxTeam; i++) {
		it = deployedUnits[i].begin();
		while(it != deployedUnits[i].end()) {
			it = find(it, deployedUnits[i].end(), 0);
			deployedUnits[i].erase(it);
		}
	}

	generate_recon_bitmap();
	generate_weapon_range_bitmap();
}

