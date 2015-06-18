#include "map.h"

Map::Map(char* filename) {
	PNG_interface::png_to_terrain_city_bitmap(filename, &terrain_bitmap, &city_bitmap);
	width = terrain_bitmap.width;
	height = terrain_bitmap.height;
	recon_bitmap.alloc(width, height, joined_teams);
	weapon_range_bitmap.alloc(width, height, joined_teams);
}

bool Map::inRange(unsigned int *bitmask, CGPoint position) {
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
	IPoint p;
	Clip cl;
	recon_bitmap.clear();
	for(int i=0; i<maxTeam; i++) {
		for(int j=0; j<maxUnit; j++) {
			u = deployedUnits[i][j];
			p = u->position;
			recon_bitmap.bit_circle(&cl, p, u->intelligenceRadius);//generate circle bit clip
			recon_bitmap.paste_clip(&cl, recon_bitmap.bitmap[i], OR);//paste to own team(i)'s layer
		}
	}
	return i * j;
}

int Map::generate_weapon_range_bitmap() const
{
	Unit* u;
	IPoint p;
	Clip cl;
	Weapon* w;
	weapon_range_bitmap.clear();
	for(int i=0; i<maxTeam; i++) {
		for(int j=0; j<maxUnit; j++) {
			u = deployedUnits[i][j];
			p = u->position;
			for(int k=0; k<maxWeapon; k++) {
				w = &weaponSlot[k];
				weapon_range_bitmap.bit_arc_circle(&cl, p, w->shootingRangeMin, w->shootingRangeMax, w->shootingAngleFrom, w->shootingAngleTo);
				weapon_range_bitmap.paste_clip(&cl, weapon_range_bitmap[i], OR);
			}
		}
	}
	return i * j;
}
