#include "Terrain.h"
#include "map.h"
#include "bitmap.h"
#define TERRAIN_COUNT 14

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

	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			p.x = x; p.y = y;
			if(image[y][x] & 0xff == 0xff) {//생산가능한 지형은 모두 블루값이 0xff임.
				c->set_pixel(p, image[y][x] & 0xff00);//도시의 고유번호를 부여함green
				switch(image[y][x]) {
					case City::color_code : 	t->set_pixel(p, city); 	break;
					case Capital::color_code : 	t->set_pixel(p, capital);break;
					case Harbor::color_code : 	t->set_pixel(p, harbor); break;
					case Airport::color_code : 	t->set_pixel(p, airport);
				}
			} 
			else {
				switch(image[y][x]) {
					case Field::color_code : 	t->set_pixel(p, field); 	break;
					case Mountain::color_code : t->set_pixel(p, mountain); 	break;
					case Sea::color_code : 		t->set_pixel(p, sea); 		break;
					case Road::color_code : 	t->set_pixel(p, road); 		break;
					case Hill::color_code : 	t->set_pixel(p, hill); 		break;
					case Swamp::color_code : 	t->set_pixel(p, swamp); 	break;
					case Fort::color_code : 	t->set_pixel(p, fort); 		break;
					case Forest::color_code : 	t->set_pixel(p, forest); 	break;
					default : 					t->set_pixel(p, river);
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
	if(city_bitmap->get_pixel(p) == 0) return NULL;
	u.team = city_bitmap->get_pixel(p);
	u.headingToward = h;
	u.position = p;
	int i;
	while (deployedUnit[u.team][i++ ] != NULL);
	deployedUnit[u.team][i] = &u;
 
	int share = (position.y * width + position.x) / intSize;//CGPoint int
	int rest = (position.y * width + position.x) % intSize;
	return *(bitmask+share+1) | 1 << (intSize-rest-1);
}

void Map::deployUnit(Unit &unit) 
{
	int i;
	while (deployedUnit[unit.team][i++ ] != null);
	deployedUnit[unit.team][i] = &unit;
}

int Map::generate_recon_bitmap() const
{
	Unit* u;
	Point<int> p;
	Clip *cl;
	recon_bitmap.clear();
	for(int i=0; i<maxTeam; i++) {
		for(int j=0; j<maxUnit; j++) {
			u = deployedUnits[i][j];
			p = u->position;
			recon_bitmap->clear();
			cl = new Clip(p, u->intelligenceRadius);
			cl->bit_circle(p, u->intelligenceRadius);//generate circle bit clip
			recon_bitmap->bitmap[i].paste_from(cl, OR);//paste to own team(i)'s layer
			delete cl;
		}
	}
	return i * j;
}

int Map::generate_weapon_range_bitmap() const
{
	Unit* u;
	Point<int> p;
	Clip *cl;
	Weapon* w;
	weapon_range_bitmap.clear();
	for(int i=0; i<maxTeam; i++) {
		for(int j=0; j<maxUnit; j++) {
			u = deployedUnits[i][j];
			p = u->position;
			for(int k=0; k<maxWeapon; k++) {
				w = &weaponSlot[k];
				cl = new Clip(p, w->shootingRangeMax);
				cl->bit_arc_circle(cl, p, w->shootingRangeMin, w->shootingRangeMax, w->shootingAngleFrom, w->shootingAngleTo);
				weapon_range_bitmap->bitmap[i].paste_from(cl, OR);
				delete cl;
			}
		}
	}
	return i * j;
}

int Map::get_log2(int cc)
{
	int i=1;//to get log 2 cc
	for (int j=2; j<cc; j *= 2) i++;
	return i;
}


