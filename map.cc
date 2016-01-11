#include <algorithm>
#include <typeinfo>
#include "Terrain.h"
#include "map.h"
#include "bitmap.h"
#include "Unit.h"
#define TERRAIN_COUNT 14
typedef unsigned char UC;

Map::Map(int w, int h, size_t **image, int ally)
{
	width = w;
	height = h;
	recon_bitmap = new Bitmap(w, h, ally);
	terrain_bitmap = new Bitmap(w, h, get_log2(TERRAIN_COUNT));
	city_bitmap = new Bitmap(w, h, get_log2(count_cities(image)));
	
	Bitmap *t = terrain_bitmap;
	Bitmap *c = city_bitmap;
	Point p;
	City ct;
	size_t dot = 0;

	for(size_t y = 0; y < h; y++) {
		for(size_t x = 0; x < w; x++) {
			p.x = x; p.y = y;
			if(image[y][x] & 0xff == 0xff) {//생산가능한 지형은 모두 블루값이 0xff임.
				dot = (image[y][x] & 0xff00) >> 2;
				c->set_pixel(p, dot);//도시의 고유번호를 부여함green
				switch(image[y][x]) {
					case City::color_code : 	t->set_pixel(p, (UC)city); 		break;
					case Capital::color_code : 	t->set_pixel(p, (UC)capital);	break;
					case Harbor::color_code : 	t->set_pixel(p, (UC)harbor);	break;
					case Airport::color_code : 	t->set_pixel(p, (UC)airport);
				}
			} else {
				switch(image[y][x]) {
					case Field::color_code : 	t->set_pixel(p, (UC)field); 	break;
					case Mountain::color_code : t->set_pixel(p, (UC)mountain); 	break;
					case Sea::color_code : 		t->set_pixel(p, (UC)sea); 		break;
					case Road::color_code : 	t->set_pixel(p, (UC)road); 		break;
					case Hill::color_code : 	t->set_pixel(p, (UC)hill); 		break;
					case Swamp::color_code : 	t->set_pixel(p, (UC)swamp); 	break;
					case Fort::color_code : 	t->set_pixel(p, (UC)fort); 		break;
					case Forest::color_code : 	t->set_pixel(p, (UC)forest); 	break;
					default : 					t->set_pixel(p, (UC)river);
				}
			}
		}
	}
}

int Map::occupy(Point p, int team)
{
	auto it = find(cities.begin(), cities.end(), city_bitmap->get_pixel(p));
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
			if(image[y][x] & 0xff == 0xff) {//생산가능한 지형은 모두 블루값이 0xff임.
				dot = (image[y][x] & 0xff00) >> 2;
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
	 return city_bitmap->get_pixel(p);
}
	
Map::~Map()
{
	delete terrain_bitmap;
	delete recon_bitmap;
	delete city_bitmap;
}

void Map::deployUnit(Unit &u, Point p, float h) 
{
	int i = city_bitmap->get_pixel(p);
	for(auto& au : cities) {//set the team according to the owner of city
		if(au.identifier == i) {
			u.set_team(au.owner);
			break;
		}
	}
	if(u.get_team() != 0) {//verify
		u.heading_toward = h;
		(Point)u = p;
		std::shared_ptr<Unit> up(new Unit(u));
		deployedUnits.push_back(up);
	}
}

int Map::generate_recon_bitmap() const
{
	Clip *cl;
	recon_bitmap->clear();
	for(auto& au : deployedUnits) {
		cl = new Clip((Point)*au, au->get_intelligenceRadius());
		cl->bit_circle((Point)*au, au->get_intelligenceRadius());//generate circle bit clip
		recon_bitmap->bitmap[au->get_ally()]->paste_from(cl, OR);//paste to get_team()team(i)'s layer
		delete cl;
	}
	return 0;
}

int Map::get_log2(int cc)
{
	int i=1;//to get log 2 cc
	for (int j=2; j<cc; j *= 2) i++;
	return i;
}

TerrainType Map::get_terrain_type(Point p)
{
	return (TerrainType)terrain_bitmap->get_pixel(p);
}

float Map::calculate_terrain_penalty(int t, WhereAbout& wh)
{ //지형의 영향력을 고려한다. 호를 100개 내지 일정한 개수의 점으로 나누어서 각 점의 지형을 샘플로 뽑아 속도를 계산한다.
	float elapse = 0;
	int i;
	TerrainType tt;
	wh.save();
	std::string s = typeid(wh).name();
	if(s == "InfantryUnit") {
		for(i=0; i < t*10; i++) {
			wh.time_pass(0.1 * i);
			tt = (TerrainType)terrain_bitmap->get_pixel(wh);
			switch(tt) {
				case city:		elapse += 10 / (100 - City::movePenaltyVsInfantry);		break;
				case capital:	elapse += 10 / (100 - Capital::movePenaltyVsInfantry); 	break;
				case harbor:	elapse += 10 / (100 - Harbor::movePenaltyVsInfantry); 	break;
				case airport:	elapse += 10 / (100 - Airport::movePenaltyVsInfantry); 	break;
				case field:		elapse += 10 / (100 - Field::movePenaltyVsInfantry); 	break;
				case mountain:	elapse += 10 / (100 - Mountain::movePenaltyVsInfantry); break;
				case river:		elapse += 10 / (100 - River::movePenaltyVsInfantry); 	break;
				case forest:	elapse += 10 / (100 - Forest::movePenaltyVsInfantry); 	break;
				case swamp:		elapse += 10 / (100 - Swamp::movePenaltyVsInfantry); 	break;
				case road:		elapse += 10 / (100 - Road::movePenaltyVsInfantry); 	break;
				case hill:		elapse += 10 / (100 - Hill::movePenaltyVsInfantry); 	break;
				case fort:		elapse += 10 / (100 - Fort::movePenaltyVsInfantry); 	break;
				case desert:	elapse += 10 / (100 - Desert::movePenaltyVsInfantry); 	break;
				case sea:		elapse += 10000; 
			}
			if(elapse >= t) break;
		}
	} else if(s == "ArmorUnit") {
		for(i=0; i < t*10; i++) {
			wh.time_pass(0.1 * i);
			tt = (TerrainType)terrain_bitmap->get_pixel(wh);
			switch(tt) {//0.1초기에 10을 나누어준다. 1초였음 100. 0.1초가 elapse로 바뀜 페널티 덕분에
				case city: 		elapse += 10 / (100 - City::movePenaltyVsArmor); 	break;
				case capital: 	elapse += 10 / (100 - Capital::movePenaltyVsArmor); break;
				case harbor: 	elapse += 10 / (100 - Harbor::movePenaltyVsArmor); 	break;
				case airport: 	elapse += 10 / (100 - Airport::movePenaltyVsArmor); break;
				case field: 	elapse += 10 / (100 - Field::movePenaltyVsArmor); 	break;
				case mountain: 	elapse += 10000;									break;
				case river: 	elapse += 10 / (100 - River::movePenaltyVsArmor); 	break;
				case forest: 	elapse += 10 / (100 - Forest::movePenaltyVsArmor); 	break;
				case swamp: 	elapse += 10 / (100 - Swamp::movePenaltyVsArmor); 	break;
				case road: 		elapse += 10 / (100 - Road::movePenaltyVsArmor); 	break;
				case hill: 		elapse += 10 / (100 - Hill::movePenaltyVsArmor); 	break;
				case fort: 		elapse += 10 / (100 - Fort::movePenaltyVsArmor); 	break;
				case desert: 	elapse += 10 / (100 - Desert::movePenaltyVsArmor); 	break;
				case sea: 		elapse += 10000; 
			}
			if(elapse >= t) break;
		}
	} else if(s == "ShipUnit") {
		for(i=0; i <= t*10; i++) {
			wh.time_pass(0.1 * i);//call the time_pass of WhereAbout<float>
			tt = (TerrainType)terrain_bitmap->get_pixel(wh);
			switch(tt) {
				case sea: 		elapse += 10 / (100 - Sea::movePenaltyVsShip); 		break;
				case river: 	elapse += 10 / (100 - River::movePenaltyVsShip); 	break;
				case harbor:	elapse += 10 / (100 - Harbor::movePenaltyVsShip); 	break;
				default: elapse += 10000; 
			}
			if(elapse >= t) break;
		}
	}
	
	return (float)i / (10 * t);
}


