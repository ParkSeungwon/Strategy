#include <algorithm>
#include <functional>
#include<cmath>
#include "Time.h"
#include "Unit.h"
#include "Terrain.h"
//#include"gtk/darea.h"//need to add gtkmm flags
#include <vector>
#include"gtk/interface.h"
using namespace std;
using namespace Glob;

TimeInterface* tInterface;

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

Time::Time()
{
	tInterface = this;
}

void Time::sync()
{//use interface to access screen
	extern FieldInterface* fInterface;
	if(deployedUnits.empty()) cout << "it's empty" << endl;
	fInterface->clear_map();
	To_draw td;
	for(auto& u : deployedUnits) {
		fInterface->paste_pix(u->x, u->y, u->file(), u->heading_toward);
		td = {u->x, u->y, 0, u->get_intelligenceRadius(), 0, 2*M_PI, 
			0.2, 0.2, 0.2, 0.2};
		fInterface->insert_to_draw(td);
		cout << u->x << u->y << u->get_unitName() << u->heading_toward << endl;
		for(auto& w : u->weapon) {
			td = {u->x, u->y, w.get_shootingRangeMin(), 
					w.get_shootingRangeMax(), 
					w.get_shootingAngleFrom() + u->heading_toward, 
					w.get_shootingAngleTo() + u->heading_toward, 
					u->get_team() / 8.0 , 0.3,0.3,0.3};
			fInterface->insert_to_draw(td);
		}
	}
	fInterface->refresh();
}

