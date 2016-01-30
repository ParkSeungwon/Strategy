#pragma once
#include <cstddef>
#include <string>

namespace Glob { 
	enum class TerrainType : char;
	enum class UnitType;
}
class Unit;

class Terrain {
public :
	static float get_move_penalty(Glob::TerrainType tt, Glob::UnitType ut);
	static float get_evade_bonus(Glob::TerrainType tt, Glob::UnitType ut); 
	static Glob::TerrainType get_terraintype_by_color(char r, char g, char b);
	const static std::string name[14];

protected :
	const static float move_penalty[4][14]; 
	const static float evade_bonus[4][14]; 
	const static char color_code[14][3]; 
};

class Land : public Terrain {
public:

};

class City : public Terrain {
public:
	void ttype(Glob::TerrainType tt) {ttype_ = tt;}
	Glob::TerrainType ttype() {return ttype_;}
	int owner() {return owner_;}
	void owner(int o) {owner_ = o;}
	int ally() {return ally_;}
	void ally(int a) {ally_ = a;}

protected:
	int owner_;
	int ally_;
	Glob::TerrainType ttype_;
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

