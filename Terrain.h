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
	enum terrainType {capital, city, airport, harbor, fort, road, mountain, sea,  field, forest, desert, swamp, hill};
		
protected:
	static int evadeBonus; 
		
public:
	Terrain();
	char* terrainBitmask(int width, int height, CGPoint center);
	
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
	City();
	lose();
};
class Airport : public City
{
public:
	Airport();
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

class Map : public Terrain 
{
private:
	unsigned int width, height;
	enum bitOption {OR, AND, XOR};
	const static int maxTeam = 8;
	const static int maxUnit = 100;
	unsigned int* make_arc_bitmap(CGPoint center, float start_angle, float end_angle);
	
	
protected:
	int bitSize, intSize;
	Bitmap* bit_circle(IPoint center, int radius);
	Bitmap* bit_flat_line(IPoint a, int longer);
	static unsigned int* bitmask(CGPoint center, int radius);
	static unsigned int* bitOperation(unsigned int *bitmaskA, unsigned int *bitmaskB, bitOption option);
	static bool inRange(unsigned int *bitmask, CGPoint position);
	unsigned int* terrainTypeBitmask;//맵에 의해 초기화된 지형, 한 좌표가 4비트를 차지 함.
	
public:
	Terrain whole_map[width][height];
	Unit* deployedUnits[maxTeam][maxUnit];
	terrainType getTerrainType(CGPoint _position);
	Map(char* filename);
	void deployUnit(Unit &unit);
};

