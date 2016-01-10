#pragma once
#include <string>
#include "Weapon.h"
#include "map.h"
#include "Waypoint.h"
#include <memory>

class Unit : public Waypoint
{
public:
	Unit(Point position, float headingToward);
	~Unit();
	int operator + (Weapon& weapon);//equip weapon
	int operator - (std::vector<Weapon>::iterator it) {weapon.erase(it);}//unload weapon
	
	//현재 설정된 프레퍼런스에 따라 배열 중 하나의 적을 선택하여 공격
	int operator >> (std::vector<std::shared_ptr<Unit>> deployed);
	
	virtual int time_pass(int time, float penalty = 1);
	Clip* recon_clip;
	bool operator==(int health) {return currentHealth <= health;}//for find function
//	Unit& operator=(Unit& u){return u;} 

	enum UnitType {Air, Armor, Infantry, Ship} unit_type;
	static std::string unitName;
	static unsigned int unitPrice;
	static unsigned int maxHealth;
	static int evadeRatio, orig_evade_ratio;//to apply terrain effect
	static int fuelCapacity;
	static int minimumTurnRadius;
	static int minimumSpeed;
	static int maximumSpeed;
	static unsigned int intelligenceRadius;

	int team, ally;
	int currentHealth;
	int fuel;
	unsigned int experience;

	std::vector<Weapon> weapon;

protected:
	void adjust_recon() const;

private:
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
};

class InfantryUnit : public TerrainUnit 
{
public:
	bool in_city();
	void out_of_city() {in_city_time = 0;}
	
private:
	int in_city_time;
};

class ShipUnit : public TerrainUnit 
{

};
