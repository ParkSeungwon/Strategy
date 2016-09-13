#pragma once
#include <string>

namespace Glob { 
	enum class TerrainType : unsigned char;
	enum class UnitType;
}
class Unit;

class Terrain {
public :
	static float get_move_penalty(Glob::TerrainType tt, Glob::UnitType ut);
	static float get_evade_bonus(Glob::TerrainType tt, Glob::UnitType ut); 
	static Glob::TerrainType get_terraintype_by_color(unsigned char r, unsigned char g, unsigned char b);
	const static std::string name[14];

protected :
	const static float move_penalty[4][14]; 
	const static float evade_bonus[4][14]; 
	const static unsigned char color_code[14][3]; 
};

class Land : public Terrain {
public:

};

class City : public Terrain {
public:
	//getter, setter
	void ttype(Glob::TerrainType tt) {ttype_ = tt;}
	Glob::TerrainType ttype() {return ttype_;}
	char id() {return id_;}
	void id(char c) {id_ = c;}
	int owner() {return owner_;}
	void owner(int o) {owner_ = o;}
	int ally() {return ally_;}
	void ally(int a) {ally_ = a;}

protected:
	char id_;//city_map_pixel number
	int owner_;
	int ally_;
	Glob::TerrainType ttype_;//capital harbor city airport
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

