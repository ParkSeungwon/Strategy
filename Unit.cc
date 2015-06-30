#include <string>
#include <vector>
using namespace std;

#include "Waypoint.h"
#include "map.h"
#include "Weapon.h"
#include "Unit.h"
#include "time.h"
#include "Terrain.h"

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
	unitName = typeid(*this);

	ifstream fin("Unit.def");
	string s;
	do {
		if (fin.eof()) throw 3; 
		fin >> s;
	}
	while (s != _unitName);
	
	fin >> maxHealth >> fuelCapacity >> unitPrice >> minimumSpeed >> maximumSpeed >> intelligenceRadius >>evadeRatio;
	fin.close();
	recon_clip = new Clip(pos, intelligenceRadius);
	recon_clip->bit_circle(pos, intelligenceRadius);
}

Unit::~Unit()
{
	delete recon_clip;
	for(int i=0; weaponSlot[i] != NULL; i++) delete weaponSlot[i];
}

Unit::move(int time)
{
	time_pass(time);
	for(int i=0; weaponSlot[i] != NULL; i++) {
		weaponSlot[i].adjust_weapon_range(this);
		ptr_weapon_range_bitmap->paste_from(weaponSlot[i].fire_range_clip, OR);
	}
	adjust_recon();
	ptr_recon_bitmap->paste_from(this->recon_clip, OR);
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

int ArmorUnit::time_pass(int time) 
{
	Nth n = nth_way(time);
	*this = waypoints[n.n];
	TerrainType tt;
	float elapse = 0;
	for(int i=0; i < n.sec * 10; i++) {
		time_pass(0.1 * i);
		tt = t_bitmap.get_pixel(position);
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

int InfantryUnit::time_pass(int time) const
{
	Nth n = nth_way(time);
	*this = waypoints[n.n];
	TerrainType tt;
	float elapse = 0;
	for(int i=0; i < n.sec * 10; i++) {
		time_pass(0.1 * i);
		tt = t_bitmap.get_pixel((int)position.x, (int)position.y);
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
	*this = waypoints[n.n];
	TerrainType tt;
	float elapse = 0;
	for(int i=0; i <= n.sec*10; i++) {
		time_pass(0.1 * i);//call the time_pass of WhereAbout<float>
		tt = t_bitmap.get_pixel((int)position.x, (int)position.y);
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
	Point<int> tc;
	distance_to(tc)
	tc.y = -1 / heading_toward * (tc.x - position.x) + position.y;
	Clip *ret = new Clip(position, maximumSpeed * time);
	Point<int> p;
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
int Unit::operator + (Weapon& w)
{
	w.fire_range_clip = new Clip(position, w.shootingRangeMax);
	adjust_weapon_range(w);
}

int InfantryUnit::occupy(City& city)
{
	city.owner = team;
	return city.identifier;
}

AirUnit::land_on(Airport& airport)
{
	
