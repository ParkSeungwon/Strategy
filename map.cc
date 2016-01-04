#include <algorithm>
#include "Terrain.h"
#include "map.h"
#include "bitmap.h"
#include "Unit.h"
#define TERRAIN_COUNT 14
typedef unsigned char UC;

Map::Map(int w, int h, size_t **image, int joined_teams)
{
	width = w;
	height = h;
	recon_bitmap = new Bitmap(w, h, joined_teams);
	weapon_range_bitmap = new Bitmap(w, h, joined_teams);
	terrain_bitmap = new Bitmap(w, h, get_log2(TERRAIN_COUNT));
	city_bitmap = new Bitmap(w, h, get_log2(count_cities(image)));
	
	Bitmap *t = terrain_bitmap;
	Bitmap *c = city_bitmap;
	Point<int> p;
	City ct;
	size_t dot = 0;

	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			p.x = x; p.y = y;
			if(image[y][x] & 0xff == 0xff) {//생산가능한 지형은 모두 블루값이 0xff임.
				dot = (image[y][x] & 0xff00) >> 2;
				c->set_pixel(p, dot);//도시의 고유번호를 부여함green
				if (find(cities.begin(), cities.end(), dot) == cities.end()) {//operator==구현 
					ct.identifier = dot;
					cities.push_back(ct);
				}
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

Map::~Map()
{
	delete terrain_bitmap;
	delete recon_bitmap;
	delete weapon_range_bitmap;
	delete city_bitmap;
}

void Map::deployUnit(Unit &u, Point<int> p, float h) 
{
	int i = city_bitmap->get_pixel(p);
	for(auto& au : cities) {//set the team according to the owner of city
		if(au.identifier == i) {
			u.team = au.owner;
			break;
		}
	}
	if(u.team != 0) {//verify
		u.heading_toward = h;
		u.position = p;
		deployedUnits[u.team].push_back(u);
	}
}

int Map::generate_recon_bitmap() const
{
	Clip *cl;
	recon_bitmap->clear();
	for(int i=0; i<maxTeam; i++) {
		for(auto& au : deployedUnits[i]) {
			cl = new Clip(au.position, au.intelligenceRadius);
			cl->bit_circle(au.position, au.intelligenceRadius);//generate circle bit clip
			recon_bitmap->bitmap[i]->paste_from(cl, OR);//paste to own team(i)'s layer
			delete cl;
		}
	}
	return 0;
}

int Map::generate_weapon_range_bitmap() const
{
	Clip *cl;
	weapon_range_bitmap->clear();
	for(int i=0; i<maxTeam; i++) {
		for(auto& u : deployedUnits[i]) {
			for(auto& w : u.weapon) {
				cl = new Clip(u.position, w.shootingRangeMax);
				cl->bit_arc_circle(u.position, w.shootingRangeMin, w.shootingRangeMax, w.shootingAngleFrom, w.shootingAngleTo);
				weapon_range_bitmap->bitmap[i]->paste_from(cl, OR);
				delete cl;
			}
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


