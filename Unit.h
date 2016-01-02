#pragma once
#include <string>
#include "Weapon.h"
#include "map.h"
#include "Waypoint.h"

class Unit : public Waypoint
{
public:
	Unit(Point<int> _position, float _headingToward);
	~Unit();
	int operator + (Weapon& weapon);//equip weapon
	int operator - (Weapon& weapon);//unload weapon
	Clip* recon_clip;
	Clip* movable_area(int time);//generate clip of movable area within time
	void move(int time);
	int operator >> (std::vector<Unit> enemy);//attack
	int capture(City& city);

	enum UnitType {Air, Armor, Infantry, Ship} unit_type;
	static std::string unitName;
	static unsigned int unitPrice;
	static unsigned int maxHealth;
	static int evadeRatio;
	static int fuelCapacity;
	static int minimumTurnRadius;
	static int minimumSpeed;
	static int maximumSpeed;
	static unsigned int intelligenceRadius;

	int team;
	int currentHealth;
	int fuel;
	unsigned int experience;

	std::vector<Weapon> weapon;

protected:
	Bitmap* terrain_bitmap;
	Bitmap* recon_bitmap;
	Bitmap* weapon_range_bitmap;

private:
	int movable_line(Point<int> turn_center, int time, Clip *cl);
};

class TerrainUnit : public Unit//지형효과를 받는 유닛들의 모클래스
{
public:
	static unsigned int terrainPenaltyPercent;
};

class AirUnit : public Unit 
{
	int land_on(Airport& airport);
};

class ArmorUnit : public TerrainUnit 
{
	int time_pass(int time);	
};

class InfantryUnit : public TerrainUnit 
{
	int time_pass(int time);
	int occupy(City& city);
};

class ShipUnit : public TerrainUnit 
{
	int time_pass(int time);

};
