#include <algorithm>
#include <functional>
#include "time.h"
#include "Unit.h"
#include "Terrain.h"
#include"gtk/darea.h"//need to add gtkmm flags
#include <vector>
using namespace std;
using namespace Glob;

void Time::time_pass()
{
	//change position
	for(auto& u : deployedUnits) {
		u->time_pass(calculate_terrain_penalty(*u)); 
		geo_effect(*u);
	}
	generate_recon();

	//attck, supply_unit
	for(auto& u : deployedUnits) {
		*u >> deployedUnits;
		u->supply(deployedUnits);
	}
	
	//remove destroyed units
	auto it = deployedUnits.begin();
	it = remove_if(it, deployedUnits.end(),
			[](shared_ptr<Unit> u){return u->get_currentHealth() <= 0;});
	it = deployedUnits.erase(it, deployedUnits.end());
	sync();
}

void Time::sync()
{
	for(auto& u : deployedUnits) {
		battlefield.paste_pix(u.x, u.y, u.get_unitName(), u.heading_toward);
		for(auto& w : u.weapon) {
			battlefield.insert_to_draw({u.x, u.y, w.get_shootingRangeMin(), 
					w.get_shootingRangeMax(), w.get_shootingAngleFrom(), 
					w.get_shootingAngleTo(), u.get_team() / 8 , 0.3,0.3,0.3});
		}
	}
}
