#include "Terrain.h"
#include "Waypoint.h"
#include <cstdlib>
#include "Unit.h"
using namespace std;

//#include <ifstream>
shared_ptr<Unit> City::produce_unit(char* unit_name, Point p, float heading_toward) {
	shared_ptr<Unit> u(new Unit(p, heading_toward));//should access Map
	u->unitName = unit_name;
	u->team = owner;
	return u;
}	
