#include <algorithm>
#include <functional>
#include "time.h"
#include "Unit.h"
#include <vector>
using namespace std;

void Time::time_pass(int time)
{
	Nth n;
	float f;
	//change position
	for(auto& u : deployedUnits) {
		n = u->nth_way(time, u->get_fuel());
		f = calculate_terrain_penalty(*u, nth.sec);
		u->time_pass(time, f); 
		u->set_evadeRatio(Terrain::get_evade_bonus(get_terrain_type(*u), u->unit_type);
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

