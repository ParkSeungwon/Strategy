//
//  Weapon.m
//  Strategygame
//
//  Created by 승원 박 on 12. 7. 13..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#include "Unit.h"
#include "Util.h"
#include "Weapon.h"

int Weapon::operator + (Unit &e) 
{
	if(currentRounds == 0) return -1;
	if(lapsedTimeAfterFire < fireRate) return -2;
	switch(e.type) {
		case AirUnit:
			return firePower * hitRatioVSAir * e.evadeRatio / 100;
		case InfantryUnit:
			return firePower * hitRatioVsInfantry * e.evadeRatio /100;
		case ArmorUnit:
			return firePower * hitRatioVsArmor * e.evadeRatio /100;
		default:
			return firePower * hitRatioVsShip * e.evadeRatio / 100;
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
	
	int dice = randomDice(100);				//0~99사이의 수를 리턴하는 유틸함수
	playSound();
	drawVisual();
	if (dice  >= hitRatio * (100 - enenmy.getEvadeRatio())/100 {
		enenmy.currentHealth -= firePower;
	}
	return dice;
}

Clip* fire_range()
{
	IPoint p; 
	p.x = shootingRangeMax + 1; 
	p.y = shootingRangeMax + 1;
	Clip* cl = new Clip(p, shootingRangeMax);
	cl->bit_arc_circle(p, shootingRangeMin, shootingRangeMax, shootingAngleFrom, shootingAngleTo);
	return cl;
}

Unit* Weapon::selectTarget() 
{
	//프레퍼런스, 체력이 0 이상, 비트마스크, 적군, 디텍티드, 
	
}

unsigned int *Weapon::bitmask(int mapWidth, int mapHeight, CGPoint unitPosition) {
	
}

Weapon::playSound() {
	cout << "Shoot !!!" <<endl;
}

Weapon::drawVisual() {
	cout << "Showing some graphics!" << endl;
}

Weapon::reload() {
	currentRounds = maxRounds;
}


