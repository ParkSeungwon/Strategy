#pragma once
#include <vector>
#include "Terrain.h"
#include "point.hpp"

class Bitmap;

class MapInterface 
{
public:
	int occupy(Point<int> p) = 0;
};

class Map : public MapInterface
{
private:
	const static int maxTeam = 8;
	int count_cities(size_t** image);
	
protected:
	
public:
	int width, height;
	std::vector<Unit> deployedUnits[maxTeam];
	std::vector<City> cities;
	Bitmap *terrain_bitmap, *recon_bitmap, *weapon_range_bitmap, *city_bitmap;
	Map(int width, int height, size_t **pixel, int teams);
	virtual ~Map();
	void deployUnit(Unit &unit, Point<int> p, float heading_toward);
	int generate_recon_bitmap() const;//return showing unit count
	int generate_weapon_range_bitmap() const;
	static int get_log2(int i);
};

