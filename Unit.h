//
//  Unit.h
//  Strategygame
//
//  Created by 승원 박 on 12. 7. 13..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

//#include <iostream>

//#include "Terrain.h"
using namespace std;

class Unit : public Waypoint<T>
{
	Unit(terrain_bitmap& tb) {t_bitmap = tb;};
	string unitName;
	const static int maxWayPoint = 10;
	int minimumSpeed;
	int maximumSpeed;
	WhereAbout positionInfo;
	Waypoint waypoint[maxWayPoint];

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
	WhereAbout position;
	Waypoint waypoint;
	
	//@property (nonatomic) int maximumAcceleration;
	unsigned int intelligenceRadius;
	
	unsigned int terrainPenaltyPercent;
	NSMutableArray *wayPoints; //CGPoint or Target Unit
	int time_pass(int time);
	int move(int start_time, int end_time);
	CGPoint getCurrentPosition() {return *this->currentPosition;}
	BOOL canEquip:(Weapon *)weapon;
	void moveToAtSpeed(CGPoint destination,int speed);
	//- (void) followOtherUnit:(Unit *)otherUnit;
	float calculateMovableRadiusForRadian:(float)radius;
	//- (void) calculateMovableAreaOnMap:(Map *)map;
	//- (void) addWayPoint:(CGPoint)destination atSpeed:(int)speed;
	
	Unit(string _unitName, CGPoint _position, float _headingToward);
;

unsigned int Unit::price;


class AirUnit : public Unit 
{
	terrainPenaltyPercent = 0;
	AirUnit(string _unitName, CGPoint _currentPosition) : Unit(_unitName, _currentPosition);
};

class ArmorUnit : public Unit 
{
	WhereAbout<> time_pass(int time);	
	int insert_waypoint(CGPoint turn, int spd, int dur);//return inserted nth waypoint
};

class InfantryUnit : public Unit 
{
	WhereAbout<> time_pass(int time);
	int insert_waypoint(CGPoint turn, int spd, int dur);//return inserted nth waypoint
};

class ShipUnit : public Unit 
{
	WhereAbout<> time_pass(int time);
};

