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
		u->set_evadeRatio(get_terrain_type(*u));
		if(in_city(*u)) {
			if(u->in_city()) occupy(*u, u->get_team());
		} else u->out_of_city();
	}
	generate_recon_bitmap();

	//attck
	for(auto& u : deployedUnits) *u >> deployedUnits;
	
	//remove destroyed units
	auto it = deployedUnits.begin();
	it = remove_if(it, deployedUnits.end(),
			[](shared_ptr<Unit> u){return u->get_currentHealth() <= 0;});
	it = deployedUnits.erase(it, deployedUnits.end());
}

