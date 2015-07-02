#pragma once
#include <vector>
#include "bitmap.h"
#include "Waypoint.h"
class Unit;

class Weapon 
{
public:
	Clip* fire_range_clip;
	int adjust_range_clip(WhereAbout<float> &wh);
	int operator >> (Unit &enenmy);		//공격 함수
	int operator >> (std::vector<Unit> enemy);//현재 설정된 프레퍼런스에 따라 배열 중 하나의 적을 선택하여 공격
	int operator + (Unit& enemy);//target return expected value regards to preference 

	Weapon();
	~Weapon();

protected:
	static int fireRate, firePower, maxRounds;
	static int hitRatioVSAir, hitRatioVsArmor, hitRatioVsInfantry, hitRatioVsShip;
	static int shootingRangeMin, shootingRangeMax;
	static int shootingAngleFrom, shootingAngleTo;
	int lapsedTimeAfterFire;
	int currentRounds;
	enum Preference {LOW_HEALTH, HIGH_DAMAGE, HIGH_RATIO, EXPENSIVE, CHEAP, NEAR} preference;
	int hitRate(Unit& enemy);
	std::vector<int> dice_record;//to record dice data for replay
};

