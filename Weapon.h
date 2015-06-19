//
//  Weapon.h
//  Strategygame
//
//  Created by 승원 박 on 12. 7. 13..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

class Weapon {

private:
	
protected:
	static int fireRate, firePower, maxRounds;
	static int hitRatioVSAir, hitRatioVsArmor, hitRatioVsInfantry, hitRatioVsShip;
	static int shootingRangeMin, shootingRangeMax;
	static int shootingAngleFrom, shootingAngleTo;
	int lapsedTimeAfterFire;
	int currentRounds;
	Clip* fire_range();//make a clip x,y=0
	enum {LOW_HEALTH, HIGH_DAMAGE, HIGH_RATIO, EXPENSIVE, CHEAP} preference;
	int operator + (Unit &enemy);//poke 프레퍼런스에 따라 높은 점수를 리턴한다.
	int hitRate(Unit& enemy);
	bool check_weapon();

public:
	int operand>>(Unit &enenmy);		//공격 함수
	int in_range(Unit &enemy);
	Unit* selectTarget();
	unsigned int *bitmask(int mapWidth, int mapHeight, CGPoint unitPosition);
	int reload();
	virtual int playSound();
	virtual int drawVisual();
	int operator + (Unit& enemy);//target return expected firepower

	int setMaxRounds(int);
	Weapon(string filename, string weaponName);

}
