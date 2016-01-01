#pragma once
#include "point.hpp"

enum TerrainType {
	city, capital, airport, harbor, mountain, forest, desert, sea, field, road, swamp, hill, river, fort
};

class Unit;

class Terrain 
{
public:
	Terrain();
	static int evadeBonus; 
	unsigned int get_color_code() {return color_code;}
	int get_movePenaltyVsShip() {return movePenaltyVsShip;}
	int get_movePenaltyVsArmor() {return movePenaltyVsArmor;}
	int get_movePenaltyVsInfantry() {return movePenaltyVsInfantry;}

protected:
	unsigned int color_code;
	int movePenaltyVsInfantry, movePenaltyVsArmor, movePenaltyVsShip; //0~100
};

class Land : public Terrain
{
public:

};

class City : public Terrain 
{
public:
	City();
	Unit* produce_unit(char* _unitName, Point<int> p, float _headingToward);
	int owner;
	int identifier;//connected pixels have same identifier, because they are one city
};

class Capital : public City
{
public:
	Capital();
	void lose();
};

class Airport : public City
{
public:
	Airport();
};

class Harbor : public City
{
public:
	Harbor();
};

class Mountain : public Land
{
public:
	Mountain();
};

class Forest : public Land
{
public:
	Forest();
};

class Desert : public Land
{
public:
	Desert();
};

class Swamp : public Land
{
public:
	Swamp();
};

class Sea : public Land
{
public:
	Sea();
};

class River : public Land
{
public:
	River();
};

class Field : public Land
{
public:
	Field();
};

class Road : public Land
{
public:
	Road();
};

class Fort : public Land
{
public:
	Fort();
};

class Hill : public Land
{
public:
	Hill();
};

