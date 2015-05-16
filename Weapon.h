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
		
	public:
		int operand>>(Unit &enenmy);		//공격 함수
		Unit* selectTarget();
		unsigned int *bitmask(int mapWidth, int mapHeight, CGPoint unitPosition);
		int reload();
		virtual int playSound();
		virtual int drawVisual();

		int setMaxRounds(int);
		Weapon(string filename, string weaponName);

}
