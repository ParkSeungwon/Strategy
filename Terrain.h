#pragma once
#include <iostream>//to pre define NULL  pointer

enum TerrainType {
	city, capital, airport, harbor, mountain, forest, desert, sea, field, road, swamp, hill, river, fort
};

class Unit;

class Terrain 
{
public:
	static int movePenaltyVsInfantry, movePenaltyVsArmor, movePenaltyVsShip; //0~100
	static int evadeBonus; 
	static unsigned int color_code;
	virtual Unit* produce_unit() = 0;
};

class Land : public Terrain
{
public:
	Unit* produce_unit() {return NULL;}//Land cannot produce Units

};

class City : public Terrain 
{
public:
	Unit* produce_unit(char* _unitName, Point<int> p, float _headingToward);
	int owner;
	int identifier;//connected pixels have same identifier, because they are one city
};

class Capital : public City
{
public:
	void lose();
};

class Airport : public City
{
public:
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
	Fort() {evadeBonus = 70;}
};

class Hill : public Land
{
public:
	Hill();
};

