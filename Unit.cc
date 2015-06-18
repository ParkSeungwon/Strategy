//
//  Unit.m
//  Straegygame
//
//  Created by 승원 박 on 12. 7. 13..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//
#include "Waypoint.h"
#include "Weapon.h"
#include "Unit.h"
#include "time.h"
#include "Terrain.h"

#include <string>

Unit::Unit(string _unitName, CGPoint _currentPosition) 
{
	ifstream fin("Unit.def");
	string s;
	do {
		if (fin.eof()) throw 3; 
		fin >> s;
	}
	while (s != _unitName)
	
	unitName = _unitName;
	currentPosition = _currentPosition;
	fin >> maxHealth >> fuelCapacity >> price >> minimumSpeed ;
	fin.close();
}

void Unit::setDirectionInRadians(float direction)
{
    while (direction >= 2 * M_PI) direction -= 2 * M_PI;
    while (direction < 0) direction += 2 * M_PI;
    _headingToward = direction;   
}

bool Unit::canEquip(Weapon *weapon) 
{
    return YES;
}

Unit::time_pass(int time) {
	move(time);
	attack(time);

	weapon.time_pass();
}

WhereAbout<> ArmorUnit::time_pass(int time)
{
	WhereAbout<float> wh;
	wh = this->position;
	TerrainType tt;
	float elapse = 0;
	for(int i=0; i < time*10; i++) {
		wh.time_pass(0.1 * i);
		tt = t_bitmap.get_pixel_data((int)wh.position.x, (int)wh.position.y);
		switch(tt) {//0.1초기에 10을 나누어준다. 1초였음 100. 0.1초가 elapse로 바뀜 페널티 덕분에
			case city: elapse += 10 / (100 - City::movePenaltyVsArmor); break;
			case capital: elapse += 10 / (100 - Capital::movePenaltyVsArmor); break;
			case harbor: elapse += 10 / (100 - Harbor::movePenaltyVsArmor); break;
			case airport: elapse += 10 / (100 - Airport::movePenaltyVsArmor); break;
			case field: elapse += 10 / (100 - Field::movePenaltyVsArmor); break;
			case mountain: elapse += 10 / (100 - Mountain::movePenaltyVsArmor); break;
			case river: elapse += 10 / (100 - River::movePenaltyVsArmor); break;
			case forest: elapse += 10 / (100 - Forest::movePenaltyVsArmor); break;
			case swamp: elapse += 10 / (100 - Swamp::movePenaltyVsArmor); break;
			case road: elapse += 10 / (100 - Road::movePenaltyVsArmor); break;
			case hill: elapse += 10 / (100 - Hill::movePenaltyVsArmor); break;
			case fort: elapse += 10 / (100 - Fort::movePenaltyVsArmor); break;
			case desert: elapse += 10 / (100 - Desert::movePenaltyVsArmor); break;
			case sea: elapse += 10000; 
		}
		if(elapse > time) break;
	}
	WhereAbout<> ret;
	ret = wh;
	return ret;
}

WhereAbout<> InfantryUnit::time_pass(int time)
{
	WhereAbout<float> wh;
	wh = this->position;
	TerrainType tt;
	float elapse = 0;
	for(int i=0; i < time*10; i++) {
		wh.time_pass(0.1 * i);
		tt = t_bitmap.get_pixel_data((int)wh.position.x, (int)wh.position.y);
		switch(tt) {
			case city:		elapse += 10 / (100 - City::movePenaltyVsInfantry);	break;
			case capital:	elapse += 10 / (100 - Capital::movePenaltyVsInfantry); break;
			case harbor:	elapse += 10 / (100 - Harbor::movePenaltyVsInfantry); break;
			case airport:	elapse += 10 / (100 - Airport::movePenaltyVsInfantry); break;
			case field:		elapse += 10 / (100 - Field::movePenaltyVsInfantry); break;
			case mountain:	elapse += 10 / (100 - Mountain::movePenaltyVsInfantry); break;
			case river:		elapse += 10 / (100 - River::movePenaltyVsInfantry); break;
			case forest:	elapse += 10 / (100 - Forest::movePenaltyVsInfantry); break;
			case swamp:		elapse += 10 / (100 - Swamp::movePenaltyVsInfantry); break;
			case road:		elapse += 10 / (100 - Road::movePenaltyVsInfantry); break;
			case hill:		elapse += 10 / (100 - Hill::movePenaltyVsInfantry); break;
			case fort:		elapse += 10 / (100 - Fort::movePenaltyVsInfantry); break;
			case desert:	elapse += 10 / (100 - Desert::movePenaltyVsInfantry); break;
			case sea:		elapse += 10000; 
		}
		if(elapse > time) break;
	}
	WhereAbout<> ret;
	ret = wh;
	return ret;
}

WhereAbout<> ShipUnit::time_pass(int time)
{
	WhereAbout<float> wh;
	wh = this->position;
	TerrainType tt;
	float elapse = 0;
	for(int i=0; i < time*10; i++) {
		wh.time_pass(0.1 * i);
		tt = t_bitmap.get_pixel_data((int)wh.position.x, (int)wh.position.y);
		switch(tt) {
			case sea: elapse += 10 / (100 - Sea::movePenaltyVsShip); break;
			case river: elapse += 10 / (100 - River::movePenaltyVsShip); break;
			case harbor: elapse += 10 / (100 - Harbor::movePenaltyVsShip); break;
			default: elapse += 10000; 
		}
		if(elapse > time) break;
	}
	WhereAbout<> ret;
	ret = wh;
	return ret;
}

int ArmorUnit::insert_waypoint(CGPoint turn, int spd, int dur)
{
	int i;
	for(i = 0; i < MAX_Waypoints; i++) {
		if(waypoints[i].duration == 0) break;
	}
	if(i < MAX_Waypoints) {
		waypoints[i].speed = spd;
		waypoints[i].turn_center = turn;
		waypoints[i].duration = dur;
		waypoints[i+1] = waypoints[i].time_pass(dur);//reach here by this waypoint
		waypoints[i+1].duration = 0;//work as a mark
	} else message("Way points limit reached!!");
	return i;
}


int Unit::move(int start, int end)//increase durong a turn, move by one_tick
{
	int dis = waypoint.moved_distance(start, end);
	if(fuel >= dis) {
		fuel -= dis;
		position = waypoint.time_pass(end);
	} else  {
		int reach = waypoint.how_long_can_i_go(start, fuel);
		fuel -= waypoint.moved_distance(start, reach);
		position = waypiont.time_pass(reach);
	} 
}
//CGPoint Unit::getTurnCenter(CGPoint destination) 
//{
//    float a = positionInfo.position.x;
//    float b = positionInfo.position.y;
//    float c = destination.x;
//    float d = destination.y;
//   
//    float cota = 1/tanf(positionInfo.headingToward);
//    CGPoint center;
//    center.x = ( (b-d)/2+(a*a-c*c)/(2*(d-b)) ) / (cota+(a-c)/(d-b));
//    center.y = cota*(a-center.x)+b;
//    return center;
//}

//float Unit::getMovedAngleInRadian(CGPoint destination) 
//{
//    CGPoint center = getTurnCenter(destination);
//    return atan2f(point.y - center.y, point.x - center.x) - atan2f(currentPosition.y - center.y, currentPosition.x - point.x); 
//}

//float Unit::getTurnRadius (CGPoint destination) 
//{
//    CGPoint center = getTurnCenter(destination);
//    return distanceBetween(destination, center);
//}


float Unit::calculateMovableDistanceForPolar(float theta) 
{
    float relativeRadius = self.headingToward + theta;
    return (2 * maximumSpeed  * cosf(relativeRadius))/ (M_PI - 2 * relativeRadius);
    
}


/*- (void)calculateMovableAreaOnMap:(Map *)map
{
    int numIterations = 0;
    float * x = malloc(numIterations*sizeof(float));
    float * cosx = malloc(numIterations*sizeof(float));
    float * sinx = malloc(numIterations*sizeof(float));
    
    for(int i=0; i < numIterations; i++){
        
        x[i] = 0;//loopCalculatedValue;
    }
    
    vvsincosf(sinx,cosx,x,&numIterations);
    //vvcosf(<#float *#>, <#const float *#>, <#const int *#>)
    
    //self.currentPosition = 
}
 */

