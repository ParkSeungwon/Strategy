#pragma once
#include <vector>
#include <memory>
#include "Terrain.h"
#include "point.hpp"
#include "Waypoint.h"

class Bitmap;

class MapInterface 
{
public:
	virtual int occupy(Point p, int team) = 0;
};

class Map : public MapInterface
{
private:
	int count_cities(size_t** image);
	static int get_log2(int i);
	
protected:
	float calculate_terrain_penalty(int time, WhereAbout& wh);
	int generate_recon_bitmap() const;//return showing unit count
	Bitmap *terrain_bitmap, *recon_bitmap, *city_bitmap;
	const static int maxTeam = 8;
	int width, height;
	
public:
	Map(int width, int height, size_t **pixel, int ally);
	virtual ~Map();
	virtual int occupy(Point p, int team);
	bool in_city(Point p);
	std::vector<std::shared_ptr<Unit>> deployedUnits;
	std::vector<City> cities;
	void deployUnit(Unit &unit, Point p, float heading_toward);
	TerrainType get_terrain_type(Point p);
};

