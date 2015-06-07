//
///
//  Created 한 글입력이 이상합니다.d
//  Terrain.m
//  xCopyright (c) __MyCompanyName__. All rights reserved.
// //

#include "Terrain.h"
#include "Waypoint.h"
#include <cstdlib>
#include <ifstream>

Terrain::Terrain() {
	movePenaltyVsInfantry = 0;
	movePenaltyVsArmor = 0;
	movePenaltyVsShip = 100;
	evadeBonus = 0;
}

City::City()
{
	movePenaltyVsInfantry = 0;
	movePenaltyVsArmor = 0;
	movePenaltyVsShip = 100;
	evadeBonus = 20;
}

Harbor::Harbor()
{
	movePenaltyVsShip = 0;
	evadeBonus = 0;
}

Sea::Sea()
{
	movePenaltyVsInfantry = 100;
	movePenaltyVsArmor = 100;
	movePenaltyVsShip = 0;
}

Forest::Forest()
{
	movePenaltyVsInfantry = 20;
	movePenaltyVsArmor = 50;
	evadeBonus = 30;
}

Hill::Hill()
{
	movePenaltyVsInfantry = 30;
	movePenaltyVsArmor = 30;
	evadeBonus = 20;
}

Mountain::Mountain()
{
	movePenaltyVsInfantry = 50;
	movePenaltyVsArmor = 100;
	evadeBonus = 60;
}

Desert::Desert()
{
	movePenaltyVsInfantry = 60;
	movePenaltyVsArmor = 20;
}

Swamp::Swamp()
{
	movePenaltyVsInfantry = 50;
	movePenaltyVsArmor = 70;
	evadeBonus = 10;
}

Map::create_terrain_bitmap(char *filename)
{
	bit_per_pixel = 4;
	
}

