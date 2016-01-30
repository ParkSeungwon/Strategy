#pragma once
#include <vector>
#include <memory>

class Unit;
class Point;
class Bitmap;
class City;
class Terrain_data;
namespace Glob {enum class TerrainType : char;}

class MapInterface 
{
public:
	virtual int occupy(Point p, int team) = 0;
};

class Map : public MapInterface
{
private:
	int count_cities(char** city_map);
	bool in_city(Point p);
	City& get_city(Point p); 
	
protected:
	float calculate_terrain_penalty(Unit& u, int time) const;
	float calculate_terrain_penalty(Unit& u) const;
	int generate_recon() const;//return showing unit count
	Glob::TerrainType **terrain_map = nullptr;
	char **city_map = nullptr;///<contains city identifier
	const static int maxTeam = 8;
	int width, height;
	
public:
	void init_map(Terrain_data&& tr, int ally);
	virtual ~Map();
	virtual int occupy(Point p, int team);
	int geo_effect(Unit& u);

	std::vector<std::shared_ptr<Unit>> deployedUnits;
	std::vector<City> cities;
	void deployUnit(Unit &unit, Point p, float heading_toward);
	Glob::TerrainType get_terrain_type(Point p) const;
};

