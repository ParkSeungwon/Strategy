#include <fstream>
#include <typeinfo>
#include <cmath>
#include "Unit.h"
#include "Util.h"
#include "bitmap.h"
using namespace std;

Unit::Unit(Point<int> pos, float heading) 
{
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

void Unit::adjust_new_position()
{
	for(auto& w : weapon) w.adjust_range_clip(*this);
	save();
	position.x -= intelligenceRadius;
	position.y -= intelligenceRadius;
	recon_clip->set_lower_left(position.to_int());
	recon_clip->clear();
	recon_clip->bit_circle(position.to_int(), intelligenceRadius);
	restore();
}

int Unit::operator + (Weapon& w)
{
	w.adjust_range_clip(*this);
	weapon.push_back(w);
}

bool InfantryUnit::in_city()
{
	in_city_time += 4;
	if(in_city_time >= 200) return true;
	else false;
}
	
