#include <fstream>
#include <typeinfo>
#include <cmath>
#include "Unit.h"
#include "Util.h"
#include "bitmap.h"
using namespace std;

Unit::Unit(Point pos, float heading) 
{
	heading_toward = heading;
	x = pos.x; y = pos.y;
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

/*Unit Unit::operator=(Unit u)
{//need more coding
	(WhereAbout)*this = u;
	return *this;
}*/

int Unit::time_pass(int t, float p)
{
	Nth n = nth_way(t, fuel);
	fuel -= n.fuel_usage;
	fuel -= WhereAbout::time_pass(n.sec, p);//this is from the start of waypoint
	for(auto& w : weapon) {
		w.time_pass();//this is from last tick	
		w.adjust_range_clip(*this);
	}
	adjust_recon();
}

void Unit::adjust_recon() const
{
	recon_clip->set_lower_left(Point(x-intelligenceRadius, y-intelligenceRadius));
	recon_clip->clear();
	recon_clip->bit_circle(*this, intelligenceRadius);
}

int Unit::operator + (Weapon w)
{
	w.adjust_range_clip(*this);
	weapon.push_back(w);
}

int Unit::operator >> (vector<shared_ptr<Unit>>& dp)
{
	int sz = dp.size();
	int* pref = new int[sz];
	int target;
	for(auto& w : weapon) {
		if(w.can_fire()) {
			for(int i=0; i<sz; i++) 
				pref[i] = can_attack(*dp[i]) ? w + *dp[i] : -1;
			target = Util::find_big(pref, sz);//배열 중 가장 값이 큰 것의 인덱스를 리턴하는 함수
			if(pref[target] > 0) w >> *dp[target];
		}
	}
	delete pref;
	return sz;
}

bool Unit::can_attack(const Unit& u)
{
	return ally != u.ally && u.known_to[ally];
}

bool InfantryUnit::in_city()
{
	Unit::in_city();
	in_city_time += 4;
	if(in_city_time >= 200) return true;
	else false;
}
	
bool Unit::in_city()
{
	fuel += 10;
	currentHealth += 1;
	for(auto& w : weapon) w.reload();
	return false;
}
