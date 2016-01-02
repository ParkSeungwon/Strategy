#pragma once
#include <memory>
#include "point.hpp"

enum TerrainType {
	city, capital, airport, harbor, mountain, forest, desert, sea, field, road, swamp, hill, river, fort
};

class Unit;

class Terrain {
public:
	const static int movePenaltyVsInfantry = 0;
	const static int movePenaltyVsArmor = 0;
	const static int movePenaltyVsShip = 100;
	const static int evadeBonus = 20;
	const static unsigned int color_code;

protected:
};

class Land : public Terrain {
public:

};

class City : public Terrain {
public:
	const static unsigned int color_code = 0xff00ff;//분홍색
	const static int movePenaltyVsInfantry = 0;
	const static int movePenaltyVsArmor = 0;
	const static int movePenaltyVsShip = 100;
	const static int evadeBonus = 20;

	std::shared_ptr<Unit> produce_unit(char* _unitName, Point<int> p, float _headingToward);
	int owner;
	int identifier;//connected pixels have same identifier, because they are one city
};

class Capital : public City {
public:
	const static unsigned int color_code = 0xaa00ff;//보라색
	const static int evadeBonus = 20;
	void lose();
};

class Airport : public City
{
public:
	const static unsigned int color_code = 0x5500ff;//연보라
	const static int evadeBonus = 0;
};

class Harbor : public City {
public:
	const static unsigned int color_code = 0x0000ff;//파란색
	const static int movePenaltyVsShip = 0;
	const static int evadeBonus = 0;
};

class Mountain : public Land {
public:
	const static unsigned int color_code = 0xff7000;//갈색
	const static int movePenaltyVsInfantry = 30;
	const static int movePenaltyVsArmor = 100;
	const static int evadeBonus = 60;
};

class Forest : public Land
{
public:
	const static unsigned int color_code = 0x007f00;//진녹색
	const static int movePenaltyVsArmor = 50;
	const static int movePenaltyVsInfantry = 20;
	const static int evadeBonus = 30;
};

class Desert : public Land
{
public:
	const static unsigned int color_code = 0xffff00;//노란색
	const static int movePenaltyVsInfantry = 60;
	const static int movePenaltyVsArmor = 20;
	const static int evadeBonus = 10;
};

class Swamp : public Land
{
public:
	const static unsigned int color_code = 0x827f00;//어두운 노란색
};

class Sea : public Land
{
public:
	const static unsigned int color_code = 0x00007f;//짙은 파란색
	const static int movePenaltyVsInfantry = 100;
	const static int movePenaltyVsArmor = 100;
	const static int movePenaltyVsShip = 0;
};

class River : public Land
{
public:
	const static unsigned int color_code = 0x007f7f;
	const static int movePenaltyVsInfantry = 70;
	const static int movePenaltyVsArmor = 70;
	const static int movePenaltyVsShip = 30;
};

class Field : public Land
{
public:
	const static unsigned int color_code = 0x00ff00;//녹색
	const static int movePenaltyVsArmor = 10;
};

class Road : public Land
{
public:
	const static unsigned int color_code = 0x000000;//검은색
};

class Fort : public Land
{
public:
	const static unsigned int color_code = 0xff0000;//빨간색 
	const static int evadeBonus = 70;
};

class Hill : public Land
{
public:
	const static unsigned int color_code = 0x7f0000;//짙은붉은색
	const static int movePenaltyVsInfantry = 30;
	const static int movePenaltyVsArmor = 30;
	const static int evadeBonus = 20;
};

