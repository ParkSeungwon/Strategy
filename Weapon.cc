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
#include "bitmap.h"
#include "Waypoint.h"
using namespace std;

Weapon::Weapon()
{
	fire_range_clip = new Clip(Point(shootingRangeMax + 1, shootingRangeMax + 1), shootingRangeMax);
}

Weapon::~Weapon()
{
	delete fire_range_clip;
}

void Weapon::adjust_range_clip(const WhereAbout &wh) const
{
	Point p;
	p.x = wh.x - shootingRangeMax;
	p.y = wh.y - shootingRangeMax;
	fire_range_clip->set_lower_left(p);
	fire_range_clip->clear();
	fire_range_clip->bit_arc_circle(p, shootingRangeMin, shootingRangeMax, shootingAngleFrom + wh.heading_toward, shootingAngleTo + wh.heading_toward);
}

int Weapon::operator + (const Unit &e) const
{
	if(e.currentHealth <= 0) return -10004;
	if(!fire_range_clip->get_pixel(e)) return -10002;
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
			fire_range_clip->lower_left.x += shootingRangeMax;
			fire_range_clip->lower_left.y += shootingRangeMax;
			return -(int)(fire_range_clip->lower_left ^ e);
	}
}

void Weapon::reload()
{
	lapsedTimeAfterFire += 4;
	currentRounds += currentRounds < maxRounds ? maxRounds / 30 : 0;
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
	int dice = rand() % 100;//0~99사이의 수를 리턴하는 유틸함수
	if (dice <= hitRatio * (100 - e.evadeRatio)/100)  e.currentHealth -= firePower;
	dice_record.push_back(dice);
	return dice;
}


