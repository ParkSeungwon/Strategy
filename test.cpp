#include<iostream>
#include"Unit.h"
#include"Util.h"
#include"mysql/mysqldata.h"
using namespace std;

int main()
{
	Waypoint p;
	WhereAbout w{{50,50}, 1.34, -300, 20, 10};
	p = w;
	cout << "this" << p.x << ' ' << p.y << endl;
	cout << w.get_turn_center().x << ' ' << w.get_turn_center().y << endl;
	cout << p.get_turn_center().x << ' ' << p.get_turn_center().y << endl;
	cout << w.x << ' ' << w.y << endl;

	Unit u{"bomber_hb", Point{1,1}, 1};
	cout << u.get_fuel() << ' ' << u.get_currentHealth() << endl;
	u.insert_waypoint(100, 50, 3, 1);
	u.insert_waypoint(-20, 3, 20, 1);
	u.insert_waypoint(20, 3, 20, 1);
	u.insert_waypoint(200, 3, 20, 1);
	u.insert_waypoint(-150, 3, 20, 1);
//	u.time_pass(1);
	for(int i=0; i<80; i++) {
		u.time_pass();
		cout << u.x << ' ' << u.y << ' ' << u.get_turn_center().x << ' ' << u.get_turn_center().y << endl;
		cout << u.get_fuel() << ' ' << u.get_currentHealth() << endl;
	}
	WhereAbout wh{Point{50,50}, 0, 30, 2, 10};
	wh.time_pass(5);
	cout << wh.x << ' ' << wh.y << ' ' << wh.get_turn_center().x << ' ' << wh.get_turn_center().y << endl;

	Waypoint wp;
	(WhereAbout)wp = wh;
	wp.insert_waypoint(-20, 3, 20, 1);
	wp.insert_waypoint(20, 3, 20, 1);
	wp.insert_waypoint(200, 3, 20, 1);
	wp.insert_waypoint(-150, 3, 20, 1);
	for(int i = 0; i < 100; i++) {
		wp.time_pass();
		cout << wp.x << ' ' << wp.y << ' ' << wp.get_turn_center().x << ' ' << wp.get_turn_center().y << endl;
	}


}
