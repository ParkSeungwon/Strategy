#pragma once
#include <vector>
class Unit;
class Clip;
template <class T> class WhereAbout;
enum Preference {LOW_HEALTH, HIGH_DAMAGE, HIGH_RATIO, EXPENSIVE, CHEAP, NEAR}; 

class Weapon 
{
public:
	Weapon();
	virtual ~Weapon();
	
	Clip* fire_range_clip;
	void adjust_range_clip(const WhereAbout<int> &wh) const;
	
	int operator + (const Unit& enemy) const;//target return expected value regards to preference 
	int operator >> (Unit &enenmy);		//공격 함수

	void set_preference(Preference p) {preference = p;}

	//getter func
	int get_currentRounds() {return currentRounds;}
	int get_lapsedTimeAfterFire() {return lapsedTimeAfterFire;}
	int get_fireRate() {return fireRate;}

protected:
	Preference preference;
	int fireRate, firePower, maxRounds;
	int hitRatioVSAir, hitRatioVsArmor, hitRatioVsInfantry, hitRatioVsShip;
	int shootingRangeMin, shootingRangeMax;
	int shootingAngleFrom, shootingAngleTo;
	int lapsedTimeAfterFire;
	int currentRounds;
	std::vector<int> dice_record;//to record dice data for replay
};

