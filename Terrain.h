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
	static unsigned int color_code;
	virtual Unit* produce_unit() = 0;
};

class Land : public Terrain
{
public:
	Unit* produce_unit() {return NULL;}

}
class City : public Terrain 
{
public:
	City();
	Unit* produce_unit(char* _unitName, float _headingToward);
	int owner;
	int identifier;//connected pixels have same identifier, because they are one city
};

unsigned int City::color_code = 0x0000ff;

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

class Field : public Land
{
public:
	Field() {movePenaltyVsArmor = 10;}
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
