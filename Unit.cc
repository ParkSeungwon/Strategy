#include <fstream>
#include <typeinfo>
#include <cmath>
#include "Unit.h"
#include "Util.h"
#include "bitmap.h"
using namespace std;

Unit::Unit(Point<int> pos, float heading, const Map& map) 
{
	terrain_bitmap = map.terrain_bitmap;
	recon_bitmap = map.recon_bitmap;
	weapon_range_bitmap = map.weapon_range_bitmap;
	city_bitmap = map.city_bitmap;
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

Unit::~Unit()
{
	delete recon_clip;
}

void Unit::move(int time)
{
	time_pass(time);
	for(auto& w : weapon) {
		w.adjust_range_clip(*this);
		weapon_range_bitmap->paste_from(w.fire_range_clip, OR);
	}
	save();
	position.x -= intelligenceRadius;
	position.y -= intelligenceRadius;
	recon_clip->set_lower_left(position.to_int());
	recon_clip->clear();
	recon_clip->bit_circle(position.to_int(), intelligenceRadius);
	recon_bitmap->paste_from(recon_clip, OR);
	restore();
}

int Unit::operator >> (vector<Unit> e)
{
	int dice;
	//for(vector<Weapon>::iterator it = weapon.begin(); it != weapon.end(); it++) dice = *it >> e;
	for(auto& au : e) {
		if(ally == au.ally) break;
		dice = au >> e;
	}
	return dice;
}
		
int ArmorUnit::time_pass(int time) 
{
	Nth n = nth_way(time);
	(WhereAbout)*this = waypoints[n.n];
	TerrainType tt;
	float elapse = 0;
	int i;
	return i;
}

int InfantryUnit::time_pass(int time) 
{

int ShipUnit::time_pass(int time) 
{
	Nth n = nth_way(time);
	(WhereAbout)*this = waypoints[n.n];
	TerrainType tt;
	float elapse = 0;
	int i;
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
	float radius = tc ^ position.to_int();
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

	
