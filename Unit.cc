#include <fstream>
#include <typeinfo>
#include <cmath>
#include "Unit.h"
#include "Util.h"
using namespace std;

Unit::Unit(Point<int> pos, float heading, Map &map) 
{
	terrain_bitmap = map.terrain_bitmap;
	recon_bitmap = map.recon_bitmap;
	weapon_range_bitmap = map.weapon_range_bitmap;
	heading_toward = heading;
	position = pos;
	currentHealth = maxHealth;
	fuel = fuelCapacity;
	experience = 0;

	ifstream fin;
	fin.open("Unit.def");
	string s;
	do {
		if (fin.eof()) throw 3; 
		fin >> s;
	}
	while (s != typeid(*this).name());
	
	fin >> maxHealth >> fuelCapacity >> unitPrice >> minimumSpeed >> maximumSpeed >> intelligenceRadius >>evadeRatio;
	fin.close();
	recon_clip = new Clip(pos, intelligenceRadius);
	recon_clip->bit_circle(pos, intelligenceRadius);
}

void Unit::move(int time)
{
	time_pass(time);
	for(vector<Weapon>::iterator it = weapon.begin(); it != weapon.end(); it++) {
		it->adjust_range_clip(*this);
		weapon_range_bitmap->paste_from(it->fire_range_clip, OR);
	}
	position - intelligenceRadius;
	recon_clip->set_lower_left(position.to_int());
	recon_clip->clear();
	recon_clip->bit_circle(position.to_int(), intelligenceRadius);
	recon_bitmap->paste_from(recon_clip, OR);
}

int Unit::attack(vector<Unit> e)
{
	int dice;
	for(vector<Weapon>::iterator it = weapon.begin(); it != weapon.end(); it++) dice = *it >> e;
	return dice;
}
		
int ArmorUnit::time_pass(int time) 
{
	Nth n = nth_way(time);
	(WhereAbout)*this = waypoints[n.n];
	TerrainType tt;
	float elapse = 0;
	int i;
	for(i=0; i < n.sec * 10; i++) {
		time_pass(0.1 * i);
		tt = (TerrainType)terrain_bitmap->get_pixel(position.to_int());
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
		if(elapse >= n.sec) break;
	}
	return i;
}

int InfantryUnit::time_pass(int time) 
{
	Nth n = nth_way(time);
	(WhereAbout)*this = waypoints[n.n];
	TerrainType tt;
	float elapse = 0;
	int i;
	for(i=0; i < n.sec * 10; i++) {
		time_pass(0.1 * i);
		tt = (TerrainType)terrain_bitmap->get_pixel(position.to_int());
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
		if(elapse >= n.sec) break;
	}
	return i;
}

int ShipUnit::time_pass(int time) 
{
	Nth n = nth_way(time);
	(WhereAbout)*this = waypoints[n.n];
	TerrainType tt;
	float elapse = 0;
	int i;
	for(i=0; i <= n.sec*10; i++) {
		time_pass(0.1 * i);//call the time_pass of WhereAbout<float>
		tt = (TerrainType)terrain_bitmap->get_pixel(position.to_int());
		switch(tt) {
			case sea: 		elapse += 10 / (100 - Sea::movePenaltyVsShip); 		break;
			case river: 	elapse += 10 / (100 - River::movePenaltyVsShip); 	break;
			case harbor:	elapse += 10 / (100 - Harbor::movePenaltyVsShip); 	break;
			default: elapse += 10000; 
		}
		if(elapse >= n.sec) break;
	}
	return i;
}

int Unit::movable_line(Point<int> tc, int time, Clip *cl)
{
	float start_angle = tc % position.to_int();
	
	save();
	speed = maximumSpeed;
	turn_center = tc;
	float angle_from = tc % position.to_int();
	Util::correct_angle(angle_from);
	time_pass(time);//call the time_pass of this Unit
	float angle_to = tc % position.to_int();
	Util::correct_angle(angle_to);
	float radius = tc - position.to_int();
	restore();
	
	if(angle_to >= angle_from) cl->bit_arc_line(tc, radius, start_angle, angle_to);
	else {
		cl->bit_arc_line(tc, radius, start_angle, 2 * M_PI);
		cl->bit_arc_line(tc, radius, 0, angle_to);
	}
	return radius * (angle_to - angle_from);
}

Clip* Unit::movable_area(int time)
{
	Clip *ret = new Clip(position.to_int(), maximumSpeed * time);
	Point<int> p;
	for(int r=minimumTurnRadius; r <= maximumSpeed * time * 10; r++) {//10? enough?
		for(int i=-1; i<= 1; i += 2) {//to calculate both side
			p = p.polar_to_xy(r, M_PI / 2 * i + heading_toward);
			p.x += position.x;
			p.y += position.y;
			movable_line(p, time, ret);//set_pixel이 OR로 작동함.
		}
	}
	return ret;
}

int Unit::operator + (Weapon& w)
{
	weapon.push_back(w);
	weapon.end()->adjust_range_clip(*this);
}

int InfantryUnit::occupy(City& city)
{
	city.owner = team;
	return city.identifier;
}

	
