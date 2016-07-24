/**
*the main class of this game---
*/
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Waypoint.h"
#include"mysql/mysqldata.h"

class Weapon;
class Airport;
namespace Glob { 
	enum class UnitType;
	enum class TerrainType : unsigned char;
}

class Unit : public Waypoint
{
public :
	Unit(std::string name, Point position, float headingToward);
	virtual ~Unit();

	std::vector<Weapon> weapon;
	int operator + (Weapon weapon);///<equip weapon
	int operator - (std::vector<Weapon>::iterator it);///<unload weapon

	///현재 설정된 프레퍼런스에 따라 배열 중 하나의 적을 선택하여 공격
	int operator >> (std::vector<std::shared_ptr<Unit>>& deployed);
	virtual int supply(std::vector<std::shared_ptr<Unit>>& deployed) {}
	
	int time_pass(float penalty = 1);
	virtual bool in_city() {return false;}
	virtual void out_of_city() {}
	bool can_attack(const Unit& u, const Weapon& w) const;
	void show();
	
	//setter, getter
	std::string get_unitName() 					{return unitName;}
	int get_evadeRatio() const 					{return evadeRatio;}
	unsigned int get_intelligenceRadius() const {return intelligenceRadius;}
	int get_ally() const 						{return ally;}
	int get_team() const						{return team;}
	int get_fuel() const 						{return fuel;}
	int get_currentHealth() const 				{return currentHealth;}
	Glob::UnitType get_unit_type() const		{return unit_type;}
	unsigned int get_unitPrice() const 			{return unitPrice;}
	bool get_supply()							{return can_supply;}
	void set_supply(bool b = true)				{can_supply = b;}
	void set_recruit(bool b = true)				{can_recruit = b;}
	void set_currentHealth(int h) 				{currentHealth = h;}
	void set_team(int t) 						{team = t;}
	void set_evadeRatio(float bonus) {evadeRatio = bonus * orig_evade_ratio;}
	void set_known_to(int i, bool b) 			{known_to[i] = b;}

protected :
	static SqlData unit_def;
	std::vector<bool> known_to = {0,0,0,0,0,0,0,0};
	std::string unitName;
	int unitPrice;
	int maxHealth;
	int evadeRatio, orig_evade_ratio;//to apply terrain effect
	int fuelCapacity;
	int minimumTurnRadius;
	int minimumSpeed;
	int maximumSpeed;
	int intelligenceRadius;
	int team, ally;
	int currentHealth;
	int fuel;
	int experience;
	Glob::UnitType unit_type;
	bool can_supply = false;
	bool can_recruit = false;


private:
};

class SupplyUnit : public Unit
{
public :
	virtual int supply(std::vector<std::shared_ptr<Unit>>& deployedUnits);
protected :
	int supply_radius = 100;
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
public :
	void set_evadeRatio(Glob::TerrainType tt) {
		evadeRatio = orig_evade_ratio * terrain_evade_bonus[(int)tt];}

//city=1, capital, airport, harbor, mountain, forest, desert, sea, field, road, swamp, hill, river, fort
private :
	const float terrain_evade_bonus[14] 
		= {1.2, 1.5, 1.1, 1, 1.2, 1.2, 1, 0.8, 1, 1, 0.5, 1.2, 1, 1.5};
};

class InfantryUnit : public TerrainUnit 
{
public:
	bool in_city();
	void out_of_city() {in_city_time = 0;}
	void set_evadeRatio(Glob::TerrainType tt) {
		evadeRatio = orig_evade_ratio * terrain_evade_bonus[(int)tt];}
	
private:
	int in_city_time;
	const float terrain_evade_bonus[14] 
		= {1.2, 1.5, 1.1, 1.1, 2, 1.2, 1, 1, 1, 1, 0.8, 1.2, 1, 1.7};
};

class ShipUnit : public TerrainUnit 
{

};
