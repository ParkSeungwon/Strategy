//
//  Terrain.h
//  Strategygame
//
//  Created by 승원 박 on 12. 7. 14..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//
  
class Terrain 
{
private:
	static int movePenaltyVsInfantry, movePenaltyVsArmor, movePenaltyVsShip; //0~100
			
protected:
	static int evadeBonus; 
		
public:
	Terrain();
};

class City : public Terrain 
{
public:
	City();
	Unit* produceUnit(char* _unitName, float _headingToward);
	int owner;
	int identifier;//connected pixels have same identifier, because they are one city
};

class Capital : public City
{
public:
	Capital() {evadeBonus = 50;}
	lose();
};
class Airport : public City
{
public:
	Airport() {evadeBonus = 0;}
};
class Harbor : public City
{
public:
	Harbor();
};
class Mountain : public Terrain
{
public:
	Mountain();
};
class Forest : public Terrain
{
public:
	Forest();
};

class Desert : public Terrain
{
public:
	Desert();
};

class Swamp : public Terrain
{
public:
	Swamp();
};

class Sea : public Terrain
{
public:
	Sea();
};

class Field : public Terrain
{
public:
	Field() {movePenaltyVsArmor = 10;}
};

class Road : public Terrain
{
public:

};

class Fort : public Terrain
{
public:
	Fort() {evadeBonus = 70;}
};

class Hill : public Terrain
{
public:
	Hill();
};
