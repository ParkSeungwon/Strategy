#include <algorithm>
#include <functional>
#include "time.h"
#include "Unit.h"
#include <vector>
using namespace std;

void Time::time_pass(int time)
{
	//change position
	for(auto& u : deployedUnits) {
		u->time_pass(time, calculate_terrain_penalty(time, *u));
		if(in_city(*u)) {
			if(u->in_city()) occupy(*u, u->team);
		} else u->out_of_city();
	}
	generate_recon_bitmap();

	//attck
	for(auto& u : deployedUnits) {
		for(auto& w : u->weapon) {
			*u >> deployedUnits;
		}
	}
	
	//remove destroyed units
	auto it = deployedUnits.begin();
	while(it != deployedUnits.end()) {
		it = find_if(it, deployedUnits.end(),//find health <=0
				[](shared_ptr<Unit> un){return un->currentHealth <= 0;});
		it = deployedUnits.erase(it);
	}
}

