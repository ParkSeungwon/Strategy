#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include "Terrain.h"
#include"mapinterface.h"

class Unit;
class Point;
class Bitmap;
class Terrain_data;
namespace Glob {enum class TerrainType : unsigned char;}

class Map : public MapInterface
{
private:
	int count_cities();
	bool in_city(Point p);
	City& get_city(Point p); 
	
protected:
	float calculate_terrain_penalty(Unit& u, int time) const;
	float calculate_terrain_penalty(Unit& u) const;
	int generate_recon() const;//return showing unit count
	Glob::TerrainType **terrain_map = nullptr;
	unsigned char **city_map = nullptr;///<contains city identifier
	const static int maxTeam = 8;
	int width, height;
	
public:
	Map();
	int init_map(Terrain_data&& tr);///<return capital count
	virtual ~Map();
	virtual int occupy(Point p, int team);
	int geo_effect(Unit& u);

	std::vector<std::shared_ptr<Unit>> deployedUnits;
//	std::vector<City> ci;
	std::unordered_map<char, City> cities;
	void deployUnit(Unit unit, Point p, float heading_toward);
	Glob::TerrainType get_terrain_type(Point p) const;
};

