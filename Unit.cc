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

Unit::Unit(terrain_bitmap *tb, recon_bitmap *rb, weapon_range_bitmap *wb)
{
	ptr_terrain_bitmap = tb;
	ptr_recon_bitmap = rb;
	ptr_weapon_range_bitmap = wb;
}

int Unit::in_range(Weapon& weapon, Unit& enemy)
{
	if(lapsedTimeAfterFire < fireRate) return 0;
	if(currentRounds <= 0) return 0;
	(enemy.position.x - position.x)
	weapon.shootingRangeMin;
	weapon.shootingRangeMax;
	weapon.shootingAngleFrom;
	weapon.shootingAngleTo;

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

WhereAbout<> ArmorUnit::time_pass(int time) const
{
	WhereAbout<float> wh = *this;
	wh = this->position;
	TerrainType tt;
	float elapse = 0;
	for(int i=0; i < time*10; i++) {
		wh.time_pass(0.1 * i);
		tt = t_bitmap.get_pixel((int)wh.position.x, (int)wh.position.y);
		switch(tt) {//0.1초기에 10을 나누어준다. 1초였음 100. 0.1초가 elapse로 바뀜 페널티 덕분에
			case city: 		elapse += 10 / (100 - City::movePenaltyVsArmor); 	break;
			case capital: 	elapse += 10 / (100 - Capital::movePenaltyVsArmor); break;
			case harbor: 	elapse += 10 / (100 - Harbor::movePenaltyVsArmor); 	break;
			case airport: 	elapse += 10 / (100 - Airport::movePenaltyVsArmor); break;
			case field: 	elapse += 10 / (100 - Field::movePenaltyVsArmor); 	break;
			case mountain: 	elapse += 10 / (100 - Mountain::movePenaltyVsArmor);break;
			case river: 	elapse += 10 / (100 - River::movePenaltyVsArmor); 	break;
			case forest: 	elapse += 10 / (100 - Forest::movePenaltyVsArmor); 	break;
			case swamp: 	elapse += 10 / (100 - Swamp::movePenaltyVsArmor); 	break;
			case road: 		elapse += 10 / (100 - Road::movePenaltyVsArmor); 	break;
			case hill: 		elapse += 10 / (100 - Hill::movePenaltyVsArmor); 	break;
			case fort: 		elapse += 10 / (100 - Fort::movePenaltyVsArmor); 	break;
			case desert: elapse += 10 / (100 - Desert::movePenaltyVsArmor); 	break;
			case sea: elapse += 10000; 
		}
		if(elapse >= time) break;
	}
	WhereAbout<> ret;
	ret = wh;
	return ret;
}

WhereAbout<int> InfantryUnit::time_pass(int time) const
{
	WhereAbout<float> wh = *this;//여기에서만 유일하게 float형이 쓰임
	TerrainType tt;
	float elapse = 0;
	for(int i=0; i < time*10; i++) {
		wh.time_pass(0.1 * i);
		tt = t_bitmap.get_pixel((int)wh.position.x, (int)wh.position.y);
		switch(tt) {
			case city:		elapse += 10 / (100 - City::movePenaltyVsInfantry);		break;
			case capital:	elapse += 10 / (100 - Capital::movePenaltyVsInfantry); 	break;
			case harbor:	elapse += 10 / (100 - Harbor::movePenaltyVsInfantry); 	break;
			case airport:	elapse += 10 / (100 - Airport::movePenaltyVsInfantry); 	break;
			case field:		elapse += 10 / (100 - Field::movePenaltyVsInfantry); 	break;
			case mountain:	elapse += 10 / (100 - Mountain::movePenaltyVsInfantry); break;
			case river:		elapse += 10 / (100 - River::movePenaltyVsInfantry); 	break;
			case forest:	elapse += 10 / (100 - Forest::movePenaltyVsInfantry); 	break;
			case swamp:		elapse += 10 / (100 - Swamp::movePenaltyVsInfantry); 	break;
			case road:		elapse += 10 / (100 - Road::movePenaltyVsInfantry); 	break;
			case hill:		elapse += 10 / (100 - Hill::movePenaltyVsInfantry); 	break;
			case fort:		elapse += 10 / (100 - Fort::movePenaltyVsInfantry); 	break;
			case desert:	elapse += 10 / (100 - Desert::movePenaltyVsInfantry); 	break;
			case sea:		elapse += 10000; 
		}
		if(elapse >= time) break;
	}
	WhereAbout<int> ret;
	ret = wh;
	return ret;
}

WhereAbout<int> ShipUnit::time_pass(int time) const
{
	WhereAbout<float> wh = *this;
	
	TerrainType tt;
	float elapse = 0;
	for(int i=0; i <= time*10; i++) {
		wh.time_pass(0.1 * i);//call the time_pass of WhereAbout<float>
		tt = t_bitmap.get_pixel((int)wh.position.x, (int)wh.position.y);
		switch(tt) {
			case sea: elapse += 10 / (100 - Sea::movePenaltyVsShip); break;
			case river: elapse += 10 / (100 - River::movePenaltyVsShip); break;
			case harbor: elapse += 10 / (100 - Harbor::movePenaltyVsShip); break;
			default: elapse += 10000; 
		}
		if(elapse >= time) break;
	}
	WhereAbout<int> ret;
	ret = wh;
	return ret;
}

int Unit::movable_line(IPoint tc, int time, Clip *cl)
{
	float start_angle = angle(tc, this->position);
	
	WhereAbout<int> wh = *this;
	this->speed = maximumSpeed;
	this->turn_center = tc;
	time_pass(time);//call the time_pass of this Unit
	float angle_to = angle(tc, this->position);
	float radius = distance_between(tc, wh.position);
	this = &wh;//restore member value
	
	if(angle_to >= start_angle) ret->bit_arc_line(tc, radius, start_angle, angle_to);
	else {
		cl->bit_arc_line(tc, radius, start_angle, 2 * M_PI);
		cl->bit_arc_line(tc, radius, 0, angle_to);
	}
	return radius * (angle_to - angle_from);
}

Clip* Unit::movable_area(int time)
{
	IPoint tc;
	distance_to(tc)
	tc.y = -1 / heading_toward * (tc.x - position.x) + position.y;
	Clip *ret = new Clip(position, maximumSpeed * time);
	IPoint p;
	for(int r=minimumTurnRadius; r <= maximumSpeed * time * 10; r++) {//10? enough?
		for(int i=-1; i<= 1; i += 2) {//to calculate both side
			p = polar_to_xy(r, M_PI / 2 * i + heading_toward);
			p.x += position.x;
			p.y += position.y;
			movable_line(p, time, ret);//set_pixel이 OR로 작동함.
		}
	}
	return ret;
}

int TerrainUnit::insert_waypoint(FPoint turn, int spd, int dur)
{
	int i;
	for(i = 0; i < MAX_Waypoints; i++) {
		if(waypoints[i].duration == 0) break;
	}
	if(i < MAX_Waypoints) {
		waypoints[i].speed = spd;
		waypoints[i].turn_center = turn;
		waypoints[i].duration = dur;
		WhereAbout *tmp = this;
		this = &waypoints[i];//maybe error
		waypoints[i+1] = time_pass(dur);//reach here by this waypoint, use own time_pass, including 지형효과
		this = tmp;
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

int Unit::operator + (Unit &e)
{
	if(!ptr_recon_bitmap->get_pixel(e.position)) return -3;
	Clip* cl;
	int arr[10];
	for(int i=0; i<maxWeapon; i++) {
		cl = weaponSlot[i].fire_range();
		cl->lower_left = position;
		if(!cl->get_pixel(e.position)) break;
		arr[i] = weaponSlot[i] + e;
	}
}
