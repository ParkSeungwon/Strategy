#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Terrain.h"
#include "map.h"
#include "Unit.h"
#include "Util.h"
#include "Weapon.h"
#include "bitmap.h"
using namespace std;
using namespace Glob;

Weapon::Weapon()
{
	fire_range_clip = new Clip( 
			Point(shootingRangeMax + 1, shootingRangeMax + 1), shootingRangeMax
			);
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
	fire_range_clip->bit_arc_circle(
			p, shootingRangeMin, shootingRangeMax, 
			shootingAngleFrom + wh.heading_toward, 
			shootingAngleTo + wh.heading_toward
			);
}

int Weapon::operator + (const Unit &e) const
{
	if(e.get_currentHealth() <= 0) return -10004;
	if(!fire_range_clip->get_pixel(e)) return -10002;
	switch(preference) {
		case HIGH_DAMAGE:
			switch(e.get_unit_type()) {
				case UnitType::Air:
					return firePower * hitRatioVSAir * e.get_evadeRatio() / 100;
				case UnitType::Infantry:
					return firePower * hitRatioVsInfantry * e.get_evadeRatio() /100;
				case UnitType::Armor:
					return firePower * hitRatioVsArmor * e.get_evadeRatio() /100;
				default:
					return firePower * hitRatioVsShip * e.get_evadeRatio() / 100;
			}
		case LOW_HEALTH: return  10000 - e.get_currentHealth();
		case EXPENSIVE: return e.get_unitPrice();
		case HIGH_RATIO:
			switch(e.get_unit_type()) {
				case UnitType::Air:
					return hitRatioVSAir * e.get_evadeRatio() / 100;
				case UnitType::Infantry:
					return hitRatioVsInfantry * e.get_evadeRatio() /100;
				case UnitType::Armor:
					return hitRatioVsArmor * e.get_evadeRatio() /100;
				default:
					return hitRatioVsShip * e.get_evadeRatio() / 100;
			}
		case CHEAP: return 10000 - e.get_unitPrice();
		case NEAR: 
			return 10000 - (int)(fire_range_clip->lower_left + 
					Point(shootingRangeMax, shootingRangeMax) ^ e);
	}
}

void Weapon::reload()
{
	currentRounds += currentRounds < maxRounds ? maxRounds / 30 : 0;
}

int Weapon::operator >> (Unit &e) 
{
	int hitRatio;
	switch (e.get_unit_type()) {
		case UnitType::Infantry:
			hitRatio = hitRatioVsInfantry;
			break;
		case UnitType::Armor:
			hitRatio = hitRatioVsArmor;
			break;
		case UnitType::Air:
			hitRatio = hitRatioVSAir;
			break;
		case UnitType::Ship:
			hitRatio = hitRatioVsShip;
	}
	
	if (hitRatio == 0) return 0;
	if (can_fire()) {
		lapsedTimeAfterFire = 0;
		currentRounds -= 1;
	}
	else return 0;
	
	srand(time(NULL));
	int dice = rand() % 100;//0~99사이의 수를 리턴하는 유틸함수
	if (dice <= hitRatio * (100 - e.get_evadeRatio())/100)  
		e.set_currentHealth(e.get_currentHealth()-firePower);
	dice_record.push_back(dice);
	return dice;
}

void Weapon::time_pass()
{
	lapsedTimeAfterFire += OneTick;
}

