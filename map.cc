#include "Terrain.h"
#include "map.h"

Map::Map(char* filename)
{
	PNG_interface::png_to_terrain_city_bitmap(filename, terrain_bitmap, city_bitmap);
	int width = terrain_bitmap->width;
	int height = terrain_bitmap->height;
	recon_bitmap = new Bitmap(width, height, joined_teams);
	weapon_range_bitmap = new Bitmap(width, height, joined_teams);
}

Map::~Map()
{
	delete terrain_bitmap;
	delete recon_bitmap;
	delete weapon_range_bitmap;
	delete city_bitmap;
}

void deployUnit(Unit &unit) 
{
	int i;
	while (deployedUnit[unit.team][i++ ] != null);
	deployedUnit[unit.team][i] = &unit;
 }
	int share = (position.y * width + position.x) / intSize;//CGPoint int
	int rest = (position.y * width + position.x) % intSize;
	return *(bitmask+share+1) | 1 << (intSize-rest-1);
}

void deployUnit(Unit &unit) 
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
