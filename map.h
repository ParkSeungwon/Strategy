#pragma once
#include <vector>
#include <memory>
//#include "Terrain.h"

class Unit;
class Point;
class Bitmap;
class City;
namespace Glob {enum class TerrainType;}

class MapInterface 
{
public:
	virtual int occupy(Point p, int team) = 0;
};

class Map : public MapInterface
{
private:
	int count_cities(size_t* image);
	static int get_log2(int i);
	bool in_city(Point p);
	City& get_city(Point p); 
	
protected:
	float calculate_terrain_penalty(Unit& u, int time) const;
	float calculate_terrain_penalty(Unit& u) const;
	int generate_recon_bitmap() const;//return showing unit count
	Bitmap *terrain_bitmap, *recon_bitmap, *city_bitmap;
	const static int maxTeam = 8;
	int width, height;
	
public:
	void initialize(int width, int height, size_t *pixel, int ally);
	Map();
	virtual ~Map();
	virtual int occupy(Point p, int team);
	int geo_effect(Unit& u);

	std::vector<std::shared_ptr<Unit>> deployedUnits;
	std::vector<City> cities;
	void deployUnit(Unit &unit, Point p, float heading_toward);
	Glob::TerrainType get_terrain_type(Point p) const;
};

