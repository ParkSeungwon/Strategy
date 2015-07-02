#pragma once
#include "Terrain.h"

class Bitmap;

class Map : public Terrain
{
private:
	const static int maxTeam = 8;
	const static int maxUnit = 100;
	
protected:
	
public:
	Unit* deployedUnits[maxTeam][maxUnit];
	Bitmap *terrain_bitmap, *recon_bitmap, *weapon_range_bitmap, *city_bitmap;
	Map(char* PNG_filename);//Read png file to init bitmaps
	void deployUnit(Unit &unit);
	int generate_recon_bitmap() const;//return showing unit count
	int generate_weapon_range_bitmap() const;
};

