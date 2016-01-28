#include <algorithm>
#include "Weapon.h"
#include "Terrain.h"
#include "map.h"
#include "bitmap.h"
#include "Unit.h"
#include "Util.h"
#include "terrain_data.h"
#define TERRAIN_COUNT 14
typedef unsigned char UC;
using namespace Glob;

void Map::init_map(Terrain_data&& tr, int ally)
{
	width = tr.width;
	height = tr.height;

	terrain_map = new TerrainType*[width];
	city_map = new char*[width];
	for(int i=0; i<width; i++) {
		terrain_map[i] = new TerrainType[height];
		city_map[i] = new char[height];
	}

	char* pc;
	for(int x=0; x<width; x++) {
		for(int y=0; y<height; y++) {
			pc = (char*)tr.tmap[x][y];
			if(pc[2] == 0xff) {
				city_map[x][y] = pc[1];
				pc[1] = 0x0;
			}
			terrain_map[x][y] = Terrain::get_terraintype_by_color(tr.tmap[x][y]);
		}
	}
}

int Map::occupy(Point p, int team)
{
	auto it = find(cities.begin(), cities.end(), city_map[p.x][p.y]);
	if(it != cities.end()) it->owner = team;
}

int Map::count_cities(size_t **image)
{
	Point p;
	size_t dot = 0;
	City ct;
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			p.x = x; p.y = y;
			if(image[x][y] & 0xff == 0xff) {//생산가능한 지형은 모두 블루값이 0xff임.
				dot = (image[x][y] & 0xff00) >> 2;
				if (find(cities.begin(), cities.end(), dot) == cities.end()) {//operator==구현 
					ct.identifier = dot;
					cities.push_back(ct);
				}
			}
		}
	}
	return cities.size();
}

bool Map::in_city(Point p) 
{
	 return city_map[p.x][p.y];
}

City& Map::get_city(Point p) 
{
	int id = city_map[p.x][p.y];
	return *find(cities.begin(), cities.end(), id);
}
	

int Map::geo_effect(Unit& u)
{
	TerrainType tt = get_terrain_type(u);
	UnitType ut = u.get_unit_type();
	u.set_evadeRatio(Terrain::get_evade_bonus(tt, ut));
	//supply
	bool ok = false;
	City& c = get_city(u);
	if(in_city(u)) {
		if(tt == TerrainType::city || tt == TerrainType::capital) {
			if(ut == UnitType::Armor || ut == UnitType::Infantry) ok = true;
		} else if(tt == TerrainType::airport && ut == UnitType::Air) ok = true;
		else if(tt == TerrainType::harbor && ut == UnitType::Ship) ok = true;
		
		if(ok && c.ally == u.get_ally()) {
			u.set_supply();
			u.set_recruit();
		}
		if(u.in_city()) occupy(u, u.get_team());
	} else u.out_of_city();

	if(ut == UnitType::Air && u.get_fuel() <= 0) {
		if(tt != TerrainType::airport || c.ally != u.get_ally()) 
			u.set_currentHealth(-100);
	}
}
		
	
Map::~Map()
{
	if(city_map != nullptr && terrain_map != nullptr) {
		for(int i=0; i<width; i++) {
			delete [] city_map[i];
			delete [] terrain_map[i];
		}
		delete city_map;
		delete terrain_map;
	}
}

void Map::deployUnit(Unit &u, Point p, float h) 
{
	City& c = get_city(p);
	u.set_team(c.owner);
	
	if(u.get_team() != 0) {//verify
		u.heading_toward = h;
		u.x = p.x; u.y = p.y;
		std::shared_ptr<Unit> up(new Unit(u));
		deployedUnits.push_back(up);
	}
}

int Map::generate_recon() const
{
	for(auto& au : deployedUnits) {
		for(auto& t : deployedUnits) {
			if((*au ^ *t) < au->get_intelligenceRadius()) 
				t->set_known_to(au->get_ally(), true);
		}
	}
	return 0;
}

int Map::get_log2(int cc)
{
	int i=1;//to get log 2 cc
	for (int j=2; j<cc; j *= 2) i++;
	return i;
}

TerrainType Map::get_terrain_type(Point p) const
{
	return terrain_map[p.x][p.y];
}

float Map::calculate_terrain_penalty(Unit& u, int time) const
{ //지형의 영향력을 고려한다. 호를 100개 내지 일정한 개수의 점으로 나누어서 각 점의 지형을 샘플로 뽑아 속도를 계산한다.
	float f, elapse = 0;
	int i, t = time;
	UnitType ut = u.get_unit_type();
	u.save();
	for(i=0; i < t*10; i++) {
		u.WhereAbout::time_pass(0.1 * i);//important casting 
		f = Terrain::get_move_penalty(get_terrain_type(u), ut);
		if(f == 0)  break;
		else elapse += 0.1 * f;
		if(elapse >= t*10) break;
	}
	u.restore();	
	return (float)i / (10 * t);
}

float Map::calculate_terrain_penalty(Unit& u) const 
{
	u.save();
	u.WhereAbout::operator=(u.waypoints[u.get_cur_waypt()]);
	float p = calculate_terrain_penalty(u, u.get_cur_time_in_waypt() + OneTick);
	u.restore();	
	return p;
}

