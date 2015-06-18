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
	Unit(terrain_bitmap& tb) {t_bitmap = tb;};
	string unitName;
	const static int maxWayPoint = 10;
	int minimumSpeed;
	int maximumSpeed;
	terrain_bitmap* ptr_terrain_bitmap;
	recon_bitmap* ptr_recon_bitmap;
	weapon_range_bitmap* ptr_weapon_range_bitmap;
	CGPoint getTurnCenter(CGPoint destination);
	//CGPoint getTurnCenterByRadiusAndTheta(float r, float theta);
	float getTurnRadius(CGPoint destination);
	float getMovedAngleInRadian(CGPoint destination);
	//CGPoint getMovedPointByRadiusAndTheta(float r, float theta);
	
	int minimumTurnRadius;
	
protected:
	static int evadeRatio;
	int fuelCapacity;
	int fuel;
	unsigned int experience;
	terrain_bitmap& t_bitmap;

public:
	int team;
	static unsigned int unitPrice;
	static unsigned int maxHealth;
	int currentHealth;
	
	Weapon* weaponSlot[10];
	unsigned int intelligenceRadius;
	
	int move(int start_time, int end_time);
	CGPoint getCurrentPosition() {return *this->currentPosition;}
	BOOL canEquip:(Weapon *)weapon;
	
	Unit(string _unitName, CGPoint _position, float _headingToward);

private:
	float distance_to(Unit& unit) const;
	float angle_to(Unit& unit) const;
};

unsigned int Unit::price;

class TerrainUnit : public Unit//지형효과를 받는 유닛들의 모클래스
{
public:
	int insert_waypoint(FPoint turn_center, int spd, int dur);//return inserted nth waypoint 지형효과를 고려함
	virtual WhereAbout<int> time_pass(int time);//버추얼
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

