#pragma once
#include"mysql/mysqldata.h"
#include <vector>
class Unit;
class Clip;
class WhereAbout;

class Weapon 
{
public:
	Weapon(std::string weaponName);
	enum Preference {LOW_HEALTH, HIGH_DAMAGE, HIGH_RATIO, EXPENSIVE, CHEAP}; 
	
	int operator + (const Unit& enemy) const;//target return expected value regards to preference 
	int operator >> (Unit &enenmy);		//공격 함수

	void set_preference(Preference p) {preference = p;}
	void time_pass();
	bool can_fire() {return currentRounds > 0 && lapsedTimeAfterFire >= fireRate;}
	void reload();

	//getter
	int get_shootingRangeMax() const {return shootingRangeMax;}
	int get_shootingRangeMin() const {return shootingRangeMin;}
	int get_shootingAngleTo() const {return shootingAngleTo;}
	int get_shootingAngleFrom() const {return shootingAngleFrom;}

protected:
	static SqlData weapon_def;
	Preference preference;
	std::string weaponName;
	int fireRate, firePower, maxRounds;
	int hitRatioVSAir, hitRatioVsArmor, hitRatioVsInfantry, hitRatioVsShip;
	int shootingRangeMin, shootingRangeMax;
	int shootingAngleFrom, shootingAngleTo;
	int lapsedTimeAfterFire;
	int currentRounds;
	std::vector<int> dice_record;//to record dice data for replay

private:
	static std::uniform_int_distribution<int> dist;
	static std::random_device rd;
};

