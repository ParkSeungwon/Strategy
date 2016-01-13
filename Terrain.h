#pragma once
#include <cstddef>

namespace Glob { 
	enum class TerrainType;
	enum class UnitType;
}
class Unit;

class Terrain {
public :
	static float get_move_penalty(Glob::TerrainType tt, Glob::UnitType ut);
	static float get_evade_bonus(Glob::TerrainType tt, Glob::UnitType ut); 
	static Glob::TerrainType get_terraintype_by_color(unsigned int code);

protected :
	const static float move_penalty[4][14]; 
	const static float evade_bonus[4][14]; 
	const static unsigned int color_code[14]; 

};

class Land : public Terrain {
public:

};

class City : public Terrain {
public:
	bool operator==(size_t id) const {return id == identifier;}

	int owner;
	int ally;
	int identifier;//connected pixels have same identifier, because they are one city
};

class Capital : public City {
public:
	void lose();
};

class Airport : public City
{
public:
};

class Harbor : public City {
public:
};

class Mountain : public Land {
public:
};

class Forest : public Land
{
public:
};

class Desert : public Land
{
public:
};

class Swamp : public Land
{
public:
};

class Sea : public Land
{
public:
};

class River : public Land
{
public:
};

class Field : public Land
{
public:
};

class Road : public Land
{
public:
};

class Fort : public Land
{
public:
};

class Hill : public Land
{
public:
};

