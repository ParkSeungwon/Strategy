#pragma once
#include <vector>
class Unit;
class Clip;
class WhereAbout;

class Weapon 
{
public:
	enum Preference {LOW_HEALTH, HIGH_DAMAGE, HIGH_RATIO, EXPENSIVE, CHEAP, NEAR}; 
	Weapon();
	virtual ~Weapon();
	
	Clip* fire_range_clip;
	void adjust_range_clip(const WhereAbout &wh) const;
	
	int operator + (const Unit& enemy) const;//target return expected value regards to preference 
	int operator >> (Unit &enenmy);		//공격 함수

	void set_preference(Preference p) {preference = p;}
	void reload() {currentRounds = maxRounds;}
	void time_pass(int time) {lapsedTimeAfterFire += time;}
	bool can_fire() {return currentRounds > 0 && lapsedTimeAfterFire >= fireRate;}

	//getter
	int get_shootingRangeMax() {return shootingRangeMax;}
	int get_shootingRangeMin() {return shootingRangeMin;}
	int get_shootingAngleTo() {return shootingAngleTo;}
	int get_shootingAngleFrom() {return shootingAngleFrom;}

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

