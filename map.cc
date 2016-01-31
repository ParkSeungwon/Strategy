#include <algorithm>
#include <iostream>
#include "Weapon.h"
#include "map.h"
#include "Unit.h"
#include "Util.h"
#include "terrain_data.h"
#define TERRAIN_COUNT 14
typedef unsigned char UC;
using namespace Glob;

int Map::init_map(Terrain_data&& tr)
{
	width = tr.width;
	height = tr.height;

	terrain_map = new TerrainType*[width];
	city_map = new unsigned char*[width];
	for(int i=0; i<width; i++) {
		terrain_map[i] = new TerrainType[height];
		city_map[i] = new unsigned char[height];
	}

	unsigned char* pc;
	for(int x=0; x<width; x++) {
		for(int y=0; y<height; y++) {
			pc = tr.pixel(x, y);
			if(pc[2] == 0xff) {//notice!! cast
				city_map[x][y] = pc[1];
				pc[1] = 0x0;
			} else city_map[x][y] = 0x0;
			terrain_map[x][y] = Terrain::get_terraintype_by_color(pc[0], pc[1], pc[2]);
		//	std::cout << (int)terrain_map[x][y] << " " ;
		}
	}
	return count_cities();	
}	

int Map::count_cities()
{
	City ct;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			ct.ttype(terrain_map[x][y]); 
			cities.emplace(city_map[x][y], ct);
		}
	}
	int c = 0;
	for(auto& a : cities) {
		std::cout << a.first << " ";
		if(a.second.ttype() == TerrainType::capital) c++;
	}
	return c;
}

Map::~Map()
{
	if(city_map != nullptr && terrain_map != nullptr) {
		for(int i=0; i<width; i++) {
			delete [] city_map[i];
			delete [] terrain_map[i];
		}
		delete [] city_map;
		delete [] terrain_map;
	}
}

int Map::occupy(Point p, int team)
{
	get_city(p).owner(team);
}

bool Map::in_city(Point p) 
{
	 return city_map[p.x][p.y];
}

City& Map::get_city(Point p) 
{
	return cities.find(city_map[p.x][p.y])->second;
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
		
		if(ok && c.ally() == u.get_ally()) {
			u.set_supply();
			u.set_recruit();
		}
		if(u.in_city()) occupy(u, u.get_team());
	} else u.out_of_city();

	if(ut == UnitType::Air && u.get_fuel() <= 0) {
		if(tt != TerrainType::airport || c.ally() != u.get_ally()) 
			u.set_currentHealth(-100);
	}
}
		
void Map::deployUnit(Unit &u, Point p, float h) 
{
	City& c = get_city(p);
	u.set_team(c.owner());
	
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

