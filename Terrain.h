//
//  Terrain.h
//  Strategygame
//
//  Created by 승원 박 on 12. 7. 14..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//
enum TerrainType city, capital, airport, harbor, mountain, forest, desert, sea, field, road, swamp, hill, river;
class Terrain 
{
private:
	static int movePenaltyVsInfantry, movePenaltyVsArmor, movePenaltyVsShip; //0~100
			
protected:
	static int evadeBonus; 
		
public:
	static unsigned int color_code;
	virtual Unit* produce_unit() = 0;
};
int Terrain::movePenaltyVsInfantry = 0;
int Terrain::movePenaltyVsArmor = 0;
int Terrain::movePenaltyVsShip = 100;
int Terrain::evadeBonus = 20;

class Land : public Terrain
{
public:
	Unit* produce_unit() {return NULL;}

}

class City : public Terrain 
{
public:
	Unit* produce_unit(char* _unitName, float _headingToward);
	int owner;
	int identifier;//connected pixels have same identifier, because they are one city
};
unsigned int City::color_code = 0xff00ff;//분홍색
int City::movePenaltyVsInfantry = 0;
int City::movePenaltyVsArmor = 0;
int City::movePenaltyVsShip = 100;
int City::evadeBonus = 20;

class Capital : public City
{
public:
	lose();
};
unsigned int Capital::color_code = 0xaa00ff;//보라색
int Capital::evadeBonus = 20;

class Airport : public City
{
public:
};
unsigned int Airport::color_code = 0x5500ff;//연보라
int Airport::evadeBonus = 0;

class Harbor : public City
{
public:
	Harbor();
};
unsigned int Harbor::color_code = 0x0000ff;//파란색
int Harbor::movePenaltyVsShip = 0;
int Harbor::evadeBonus = 0;

class Mountain : public Land
{
public:
	Mountain();
};
unsigned int Mountain::color_code = 0xff7000;//갈색
int Mountain::movePenaltyVsInfantry = 30;
int Mountain::movePenaltyVsArmor = 100;
int Mountain::evadeBonus = 60;

class Forest : public Land
{
public:
	Forest();
};
unsigned int Forest::color_code = 0x007f00;//진녹색
int Forest::movePenaltyVsArmor = 50;
int Forest::movePenaltyVsInfantry = 20;
int Forest::evadeBonus = 30;

class Desert : public Land
{
public:
	Desert();
};
unsigned int Desert::color_code = 0xffff00;//노란색
int Desert::movePenaltyVsInfantry = 60;
int Desert::movePenaltyVsArmor = 20;

class Swamp : public Land
{
public:
	Swamp();
};
unsigned int Swamp::color_code = 0x827f00;//어두운 노란색
int Desert::movePenaltyVsInfantry = 50;
int Desert::movePenaltyVsArmor = 70;
int Desert::evadeBonus = 10;

class Sea : public Land
{
public:
	Sea();
};
unsigned int Sea::color_code = 0x00007f;//짙은 파란색
int Sea::movePenaltyVsInfantry = 100;
int Sea::movePenaltyVsArmor = 100;
int Sea::movePenaltyVsShip = 0;

class River : public Land
{
public:
};
unsigned int River::color_code = 0x0;
int River::movePenaltyVsInfantry = 70;
int River::movePenaltyVsArmor = 70;
int River::movePenaltyVsShip = 30;

class Field : public Land
{
public:
};
unsigned int Field::color_code = 0x00ff00;//녹색
int Field::movePenaltyVsArmor = 10;

class Road : public Land
{
public:

};
unsigned int Road::color_code = 0x000000;//검은색

class Fort : public Land
{
public:
	Fort() {evadeBonus = 70;}
};
unsigned int Fort::color_code = 0xff0000;//빨간색

class Hill : public Land
{
public:
	Hill();
};
unsigned int Hill::color_code = 0x7f0000//짙은붉은색
int Hill::movePenaltyVsInfantry = 30;
int Hill::movePenaltyVsArmor = 30;
int Hill::evadeBonus = 20;

