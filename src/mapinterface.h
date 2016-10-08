#include"Util.h"
class Point;
class Terrain_data;

struct MapInterface 
{
	virtual std::string occupy(Point p, int team) = 0;
	virtual Glob::TerrainType get_terrain_type(Point p) const = 0;
	virtual City& get_city(Point p) = 0;
	virtual void deployUnit(Unit unit, Point p, float heading_toward) = 0;
	virtual Unit& getUnit(Point p) = 0;
};
