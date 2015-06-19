//
//  Unit.h
//  Strategygame
//
//  Created by 승원 박 on 12. 7. 13..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

//#include <iostream>

//#include "Terrain.h"

class Unit : public Waypoint<T>
{
public:
	int team;
	static unsigned int unitPrice;
	static unsigned int maxHealth;
	int currentHealth;
	int minimumTurnRadius;
	int minimumSpeed;
	int maximumSpeed;
	Weapon* weaponSlot[10];
	unsigned int intelligenceRadius;

	Clip* movable_area(int time);//generate clip of movable area within time
	
	BOOL canEquip:(Weapon *)weapon;
	
	Unit(string _unitName, CGPoint _position, float _headingToward);

	Unit(terrain_bitmap& tb) {t_bitmap = tb;};
	string unitName;
	const static int maxWayPoint = 10;
	terrain_bitmap* ptr_terrain_bitmap;
	recon_bitmap* ptr_recon_bitmap;
	weapon_range_bitmap* ptr_weapon_range_bitmap;

	Clip* movable_area(int time);
	int operator + (Unit& enemy);//target enemy, return 기대값 
	
	
protected:
	static int evadeRatio;
	int fuelCapacity;
	int fuel;
	unsigned int experience;


private:
	int movable_line(IPoint turn_center, int time, Clip *cl);
};

unsigned int Unit::price;

class TerrainUnit : public Unit//지형효과를 받는 유닛들의 모클래스
{
public:
	int insert_waypoint(FPoint turn_center, int spd, int dur);//return inserted nth waypoint 지형효과를 고려함
	static unsigned int terrainPenaltyPercent;
};

class AirUnit : public Unit 
{
	terrainPenaltyPercent = 0;
	AirUnit(string _unitName, CGPoint _currentPosition) : Unit(_unitName, _currentPosition);
};

class ArmorUnit : public TerrainUnit 
{
	WhereAbout<int> time_pass(int time);	
};

class InfantryUnit : public TerrainUnit 
{
	WhereAbout<int> time_pass(int time);
};

class ShipUnit : public TerrainUnit 
{
	WhereAbout<int> time_pass(int time);

};

