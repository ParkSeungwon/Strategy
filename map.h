#pragma once
#include <vector>
#include "Terrain.h"
#include "point.hpp"
#include "Waypoint.h"

class Bitmap;

class MapInterface 
{
public:
	virtual int occupy(Point<int> p, int team) = 0;
};

class Map : public MapInterface
{
private:
	int count_cities(size_t** image);
	
protected:
	const static int maxTeam = 8;
	
public:
	virtual int occupy(Point<int> p, int team);
	int width, height;
	std::vector<Unit> deployedUnits;
	std::vector<City> cities;
	Bitmap *terrain_bitmap, *recon_bitmap, *weapon_range_bitmap, *city_bitmap;
	Map(int width, int height, size_t **pixel, int teams);
	virtual ~Map();
	void deployUnit(Unit &unit, Point<int> p, float heading_toward);
	int generate_recon_bitmap() const;//return showing unit count
	int generate_weapon_range_bitmap() const;
	static int get_log2(int i);
	float calculate_terrain_penalty(int time, WhereAbout<>& wh);
};

