//
//  Terrain.h
//  Strategygame
//
//  Created by 승원 박 on 12. 7. 14..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//



class Unit;

class Terrain {
	private:
		int movePenaltyVsInfantry, movePenaltyVsArmor, movePenaltyVsShip; 
		enum terrainType {capital, city, airport, harbor, fort, road, mountain, sea,  field, forest, desert, swamp, hill};
		
	protected:
		int evadeBonus; 
		
	public:
		Terrain();
		char* terrainBitmask(int width, int height, CGPoint center);
		Unit* produceUnit(char* _unitName, float _headingToward);
};

class Map : public Terrain {
	private:
		int width, height;
		int bitSize, intSize;
		enum bitOption {OR, AND, XOR};
		const static int maxTeam = 8;
		const static int maxUnit = 100;
	
	protected:
		static unsigned int* bitmask(CGPoint center, int radius);
		static unsigned int* bitOperation(unsigned int *bitmaskA, unsigned int *bitmaskB, bitOption option);
		static bool inRange(unsigned int *bitmask, CGPoint position);
		unsigned int* terrainTypeBitmask;		//맵에 의해 초기화된 지형, 한 좌표가 4비트를 차지 함.
	
	public:
		Unit* deployedUnits[maxTeam][maxUnit];
		terrainType getTerrainType(CGPoint _position);
		Map(char* filename);
		void deployUnit(Unit &unit);
};
