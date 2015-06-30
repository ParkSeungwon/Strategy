//#include "Unit.h"
#include <stdio.h>
#include "point.hpp"
#include "Waypoint.h"
#include "Terrain.h"
#include "map.h"
#include "Unit.h"
#include "bitmap.h"
#include "Weapon.h"

Weapon::Weapon()
{
	fire_range_clip = new Clip(Point<int>(shootingRangeMax + 1, shootingRangeMax + 1), shootingRangeMax);

	dice_record = new int[TURN_TIME / fireRate];//maximum attack possible
	current_dice = dice_record;
}

Weapon::~Weapon()
{
	delete fire_range_clip;
	delete dice_record;
}

int Weapon::adjust_range_clip(WhereAbout& wh)
{
	fire_range_clip->lower_left.x = wh.position.x - shootingRangeMax;
	fire_range_clip->lower_left.y = wh.position.y - shootingRangeMax;
	fire_range_clip->bit_arc_circle(wh.position, shootingRangeMin, shootingRangeMax, shootingAngleFrom + wh.heading_toward, shootingAngleTo + wh.heading_toward);
}

int Weapon::operator + (Unit &e) 
{
	if(currentRounds <= 0) return -10000;
	if(lapsedTimeAfterFire < fireRate) return -10001;
	if(e.currentHealth <= 0) return -10004;
	if(!fire_range_clip->get_pixel(e)) return -10002;
	switch(preference) {
		case HIGH_DAMAGE:
			switch(typeid(e)) {
				case AirUnit:
					return firePower * hitRatioVSAir * e.evadeRatio / 100;
				case InfantryUnit:
					return firePower * hitRatioVsInfantry * e.evadeRatio /100;
				case ArmorUnit:
					return firePower * hitRatioVsArmor * e.evadeRatio /100;
				default:
					return firePower * hitRatioVsShip * e.evadeRatio / 100;
			}
		case LOW_HEALTH: return  -e.currentHealth;
		case EXPENSIVE: return e.unitPrice;
		case HIGH_RATIO:
			switch(typeid(e)) {
				case AirUnit:
					return hitRatioVSAir * e.evadeRatio / 100;
				case InfantryUnit:
					return hitRatioVsInfantry * e.evadeRatio /100;
				case ArmorUnit:
					return hitRatioVsArmor * e.evadeRatio /100;
				default:
					return hitRatioVsShip * e.evadeRatio / 100;
			}
		case CHEAP: return -e.unitPrice;
	}
}

int Weapon::operator >> (Unit &e) 
{
	int hitRatio;
	switch type(enenmy) {
		case: InfantryUnit
			hitRatio = hitRatioVsInfantry;
			break;
		case: ArmorUnit
			hitRatio = hitRatioVsArmor;
			break;
		case: AirUnit
			hitRatio = hitRatioVSAir;
			break;
		case: ShipUnit
			hitRatio = hitRatioVsShip;
	}
	
	if (hitRatio == 0) return 0;
	if (lapsedTimeAfterFire >= fireRate && currentRounds >=1) {
		lapsedTimeAfterFire = 0;
		currentRounds -= 1;
	}
	else return 0;
	
	int dice;
	if(*current_dice == 0) {//if this is not replay
		dice = randomDice(100);//1~100사이의 수를 리턴하는 유틸함수
		*current_dice = dice;
	} else dice = *current_dice;
	current_dice++;

	playSound();
	drawVisual();
	if (dice  >= hitRatio * (100 - e.evadeRatio)/100 {
		e.currentHealth -= firePower;
	}
	return dice;
}

int Weapon::operator >> (Unit* e[])
{
	int pref[MAX_UNIT];
	for(int i=0; e[i] != NULL; i++) int pref[i] = *this + *e[i];
	int target = find_big(pref);//배열 중 가장 값이 큰 것의 인덱스를 리턴하는 함수
	int dice = *this >> *e[target];
	return dice;
}
