#include<iostream>
#include"Unit.h"
#include"Util.h"
#include"Weapon.h"
#include"mysqldata.h"
#include"gtk/interface.h"
#include"mapinterface.h"
using namespace std;

extern FieldInterface* fInterface;
vector<array<int, 3>> setup(int capital_count);

int main()
{
	Unit u{"British", "bomber_hb", Point{200,100}, M_PI};
	u.show();
	cout << "position " << u.x << ' ' << u.y << endl;
	cout << u.get_fuel() << ' ' << u.get_currentHealth() << endl;
	u.insert_waypoint(100, 50, 3, 1);
	u.show();
	u.insert_waypoint(-20, 3, 20);
	u.insert_waypoint(20, 3, 20);
	u.insert_waypoint(200, 3, 20);
	u.insert_waypoint(-150, 7, 20);
	Weapon w{"side-winder"};
//	u.time_pass(1);
	for(int i=0; i<60; i++) {
		w.time_pass();
		u.time_pass();
		//fInterface->paste_pix(u.x, u.y, u.get_unitName(), u.heading_toward);
		u.show();
		w >> u;
		u.show();
	}

	extern MapInterface* mInterface;
	mInterface->deployUnit(u, u, 0);
	u + w;
	Unit e{"Chinese", "bomber_hb", {40, 320}, 0};
	cout << w + e;
	w.time_pass(); 
	w >> u;
	u.show();
}
