#pragma once
#include <memory>
#include <unordered_map>
#include "point.hpp"

class Unit;
enum UnitType {Air, Armor, Infantry, Ship};

class Terrain {
public :
	enum TerrainType {
		city, capital, airport, harbor, mountain, forest, desert, sea, field, road, swamp, hill, river, fort
	};
	static float get_move_penalty(TerrainType tt, UnitType ut) {
		return move_penalty[ut][tt];}
	static float get_evade_bonus(TerrainType tt, UnitType ut) {
		return evade_bonus[ut][tt];}
	static TerrainType get_terraintype_by_color(unsigned int code);

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

