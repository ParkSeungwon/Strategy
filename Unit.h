#pragma once
#include <string>
#include "Weapon.h"
#include "map.h"
#include "Waypoint.h"
#include <memory>

class Unit : public Waypoint
{
public :
	Unit(Point position, float headingToward);
	~Unit();
	int operator + (Weapon weapon);//equip weapon
	int operator - (std::vector<Weapon>::iterator it) {weapon.erase(it);}//unload weapon
	
	//현재 설정된 프레퍼런스에 따라 배열 중 하나의 적을 선택하여 공격
	int operator >> (std::vector<std::shared_ptr<Unit>>& deployed);
	
	int time_pass(int time, float penalty = 1);
//	bool operator==(int health) {return currentHealth <= health;}//for find function
//	Unit& operator=(Unit& u){return u;} 
	virtual bool in_city();
	virtual void out_of_city() {}
	virtual void set_evadeRatio(TerrainType tt) {evadeRatio = orig_evade_ratio;}
	
	std::vector<Weapon> weapon;
	enum UnitType {Air, Armor, Infantry, Ship} unit_type;

	//setter, getter
	int get_evadeRatio() const 					{return evadeRatio;}
	unsigned int get_intelligenceRadius() const {return intelligenceRadius;}
	int get_ally() const 						{return ally;}
	int get_team() const						{return team;}
	int get_currentHealth() const 				{return currentHealth;}
	unsigned int get_unitPrice() const 			{return unitPrice;}
	void set_currentHealth(int h) 				{currentHealth = h;}
	void set_team(int t) 						{team = t;}

protected :
	void adjust_recon() const;
	
	Clip* recon_clip;
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
public :
	void set_evadeRatio(TerrainType tt) {
		evadeRatio = orig_evade_ratio * terrain_evade_bonus[tt];}

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
	void set_evadeRatio(TerrainType tt) {
		evadeRatio = orig_evade_ratio * terrain_evade_bonus[tt];}
	
private:
	int in_city_time;
	const float terrain_evade_bonus[14] 
		= {1.2, 1.5, 1.1, 1.1, 2, 1.2, 1, 1, 1, 1, 0.8, 1.2, 1, 1.7};
};

class ShipUnit : public TerrainUnit 
{

};
