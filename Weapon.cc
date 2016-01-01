//#include "Unit.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "point.hpp"
#include "Terrain.h"
#include "map.h"
#include "Unit.h"
#include "Util.h"
#include "Weapon.h"
using namespace std;

Weapon::Weapon()
{
	fire_range_clip = new Clip(Point<int>(shootingRangeMax + 1, shootingRangeMax + 1), shootingRangeMax);
}

Weapon::~Weapon()
{
	delete fire_range_clip;
}

int Weapon::adjust_range_clip(WhereAbout<float> &wh)
{
	wh.position - shootingRangeMax;
	fire_range_clip->set_lower_left(wh.position.to_int());
	fire_range_clip->clear();
	fire_range_clip->bit_arc_circle(wh.position.to_int(), shootingRangeMin, shootingRangeMax, shootingAngleFrom + wh.heading_toward, shootingAngleTo + wh.heading_toward);
}

int Weapon::operator + (Unit &e) 
{
	if(currentRounds <= 0) return -10000;
	if(lapsedTimeAfterFire < fireRate) return -10001;
	if(e.currentHealth <= 0) return -10004;
	if(!fire_range_clip->get_pixel(e.position.to_int())) return -10002;
	switch(preference) {
		case HIGH_DAMAGE:
			switch(e.unit_type) {
				case Unit::Air:
					return firePower * hitRatioVSAir * e.evadeRatio / 100;
				case Unit::Infantry:
					return firePower * hitRatioVsInfantry * e.evadeRatio /100;
				case Unit::Armor:
					return firePower * hitRatioVsArmor * e.evadeRatio /100;
				default:
					return firePower * hitRatioVsShip * e.evadeRatio / 100;
			}
		case LOW_HEALTH: return  -e.currentHealth;
		case EXPENSIVE: return e.unitPrice;
		case HIGH_RATIO:
			switch(e.unit_type) {
				case Unit::Air:
					return hitRatioVSAir * e.evadeRatio / 100;
				case Unit::Infantry:
					return hitRatioVsInfantry * e.evadeRatio /100;
				case Unit::Armor:
					return hitRatioVsArmor * e.evadeRatio /100;
				default:
					return hitRatioVsShip * e.evadeRatio / 100;
			}
		case CHEAP: return -e.unitPrice;
		case NEAR: 
			fire_range_clip->lower_left + shootingRangeMax;
			return -(fire_range_clip->lower_left - e.position.to_int());
	}
}

int Weapon::operator >> (Unit &e) 
{
	int hitRatio;
	switch (e.unit_type) {
		case Unit::Infantry:
			hitRatio = hitRatioVsInfantry;
			break;
		case Unit::Armor:
			hitRatio = hitRatioVsArmor;
			break;
		case Unit::Air:
			hitRatio = hitRatioVSAir;
			break;
		case Unit::Ship:
			hitRatio = hitRatioVsShip;
	}
	
	if (hitRatio == 0) return 0;
	if (lapsedTimeAfterFire >= fireRate && currentRounds >=1) {
		lapsedTimeAfterFire = 0;
		currentRounds -= 1;
	}
	else return 0;
	
	srand(time(NULL));
	int dice = rand() % 100;//1~100사이의 수를 리턴하는 유틸함수
	if (dice >= hitRatio * (100 - e.evadeRatio)/100) {
		e.currentHealth -= firePower;
	}
	dice_record.push_back(dice);
	return dice;
}

int Weapon::operator >> (vector<Unit> e)
{
	//int pref[e.size()];
	int* pref = new int[e.size()];
	int i = 0;
	for(auto& a : e) pref[i++] = *this + a;
	int target = Util::find_big(pref, e.size());//배열 중 가장 값이 큰 것의 인덱스를 리턴하는 함수
	int dice = *this >> e[target];
	delete pref;
	return dice;
}
