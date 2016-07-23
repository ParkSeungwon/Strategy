#include<iostream>
#include"Unit.h"
#include"Util.h"
#include"mysql/mysqldata.h"
using namespace std;

int main()
{
	Unit u{"bomber_hb", Point{200,100}, M_PI};
	u.show();
	cout << "position " << u.x << ' ' << u.y << endl;
	cout << u.get_fuel() << ' ' << u.get_currentHealth() << endl;
	u.insert_waypoint(100, 50, 3, 1);
	u.show();
	u.insert_waypoint(-20, 3, 20, 1);
	u.insert_waypoint(20, 3, 20, 1);
	u.insert_waypoint(200, 3, 20, 1);
	u.insert_waypoint(-150, 7, 20, 1);
//	u.time_pass(1);
	for(int i=0; i<90; i++) {
		u.time_pass();
		u.show();
	}
}
