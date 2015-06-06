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
	enum terrainType {Road, Fort, Mountain, Sea, Field, Forest, Desert, Swamp, Hill, City, Capital, Airport, Harbor};
		
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
	const static int maxTeam = 8;
	const static int maxUnit = 100;
	
protected:
	static unsigned int* bitmask(CGPoint center, int radius);
	static unsigned int* bitOperation(unsigned int *bitmaskA, unsigned int *bitmaskB, bitOption option);
	static bool inRange(unsigned int *bitmask, CGPoint position);
	Bitmap terrain_bitmap, unit_bitmap, recon_bitmap, wepon_range_bitmap, city_bitmap;
	create_terrain_bitmap();
	
public:
	Terrain whole_map[width][height];
	Unit* deployedUnits[maxTeam][maxUnit];
	terrainType getTerrainType(CGPoint _position);
	Map(char* filename);
	void deployUnit(Unit &unit);
};

