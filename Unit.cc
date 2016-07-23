#include<string>
#include "Unit.h"
#include "Util.h"
#include "Weapon.h"
using namespace std;
using namespace Glob;

SqlData Unit::unit_def {};

Unit::Unit(string name, Point pos, float heading) 
{
	if(unit_def.empty()) {
		SqlQuery sd;
		sd.connect("localhost", "strategy", "strategy", "strategy");
		sd.select("Units");
		unit_def = move(sd);
	}
	for(auto& a : unit_def) {
		if(a[0] == name) {
			maxHealth = a[1];
			fuelCapacity = a[2];
			unitPrice = a[3];
			minimumSpeed = a[4];
			maximumSpeed = a[5];
			intelligenceRadius = a[6];
			minimumTurnRadius = a[7];
			evadeRatio = a[8];
			break;
		}
	}
	unitName = name;
	heading_toward = heading;
	x = pos.x; y = pos.y;
	currentHealth = maxHealth;
	fuel = fuelCapacity;
	experience = 0;
	speed = 0;
}

Unit::~Unit()
{
}

/*Unit Unit::operator=(Unit u)
{//need more coding
	(WhereAbout)*this = u;
	return *this;
}*/

void Unit::show()
{
	cout << unitName << ' ' << "HP=" << currentHealth << ", x=" << x << ",y=" << y;
	cout << ", turnx=" << turn_center.x << ", turny=" << turn_center.y;
	cout << ", fuel=" << fuel << ", speed=" << speed;
	cout << ", heading=" << heading_toward << endl;
}

int Unit::time_pass(float p)
{
	int fuel_use = OneTick * waypoints[cur_waypt].speed; 
	if(fuel_use <= fuel) {
		Waypoint::time_pass(p);
		fuel -= fuel_use;
	}
	for(auto& w : weapon) {
		w.time_pass();//this is from last tick	
	}
	if(can_supply) {
		for(auto& w : weapon) w.reload();
		fuel += 10 * OneTick;
		can_supply = false;
	}
	if(can_recruit) {
		currentHealth += OneTick;
		can_recruit = false;
	}
	return fuel;
}

int Unit::operator+(Weapon w)
{
	weapon.push_back(w);
}

int Unit::operator-(std::vector<Weapon>::iterator it)
{
	weapon.erase(it);
}

int Unit::operator >> (vector<shared_ptr<Unit>>& dp)
{
	int sz = dp.size();
	int* pref = new int[sz];
	int target;
	for(auto& w : weapon) {
		if(w.can_fire()) {
			for(int i=0; i<sz; i++) pref[i] = can_attack(*dp[i], w) ? w + *dp[i] : -1;
			target = find_big(pref, sz);//배열 중 가장 값이 큰 것의 인덱스를 리턴하는 함수
			if(pref[target] > 0) w >> *dp[target];
		}
	}
	delete pref;
	return sz;
}

int SupplyUnit::supply(vector<shared_ptr<Unit>>& dp)
{
	for(auto& u : dp) {
		if((*this ^ *u) < supply_radius && u->get_ally() == get_ally()) 
			u->set_supply(true);
	}
	return 0;
}

bool Unit::can_attack(const Unit& u, const Weapon& w) const
{
	if(ally != u.ally && u.known_to[ally]) {
		float distance = *this ^ u;
		if(distance >= w.get_shootingRangeMin() && distance <= w.get_shootingRangeMax()) {
			float angle = *this % u;
			if(angle >= heading_toward + w.get_shootingAngleFrom() 
					&& angle <= heading_toward + w.get_shootingAngleTo()) {
			   return true;
		   }
		}
	} 
	return false;
}

bool InfantryUnit::in_city()
{
	in_city_time += 4;
	if(in_city_time >= 200) return true;
	return false;
}
