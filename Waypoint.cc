#include <typeinfo>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "point.hpp"
#include "Waypoint.h"
#include "Util.h"

template <class T> float WhereAbout<T>::correct_angle(float f)
{
	while(f >= M_PI) f -= M_PI;
	while(f < 0) f += M_PI;
	return f;
}

template <class T> int WhereAbout<T>::time_pass(T time)
{
//	if(duration == 0) return *this;
	if(time > duration) time = duration;
	T x = position.x - turn_center.x;
	T y = position.y - turn_center.y;
	float r = sqrtf(x*x + y*y);
	float center_angle = acosf(x/r);
	if(y > 0) center_angle += M_PI; //현 위치에서 센터로 가는 벡터의 각도
	float theta = speed * time / r;
	
	float diff = abs(center_angle - correct_angle(heading_toward + M_PI/2));
	if(diff < 0.1 || diff > 3) { //if center is at the left of heading direction
		heading_toward += theta;
		position.x = turn_center.x + r * cosf(center_angle + theta);
		position.y = turn_center.y + r * sinf(center_angle + theta);
	} else {
		heading_toward -= theta;
		position.x = turn_center.x + r * cosf(center_angle - theta);
		position.y = turn_center.y + r * sinf(center_angle - theta);
	}
	duration -= time;//left duration of this waypiont
	return duration;
}


int Waypoint::time_pass(int time)
{
	Nth n = nth_way(time);
	(WhereAbout)*this = waypoints[n.n];
	time_pass(n.sec);
	return n.sec;
}

template <class T> int WhereAbout<T>::operator = (WhereAbout<int> &wh)
{
	position = wh.position;
	turn_center = wh.turn_center;
	speed = wh.speed;
	heading_toward = wh.heading_toward;
	duration = (T)wh.duration;
	return duration;
}

int Waypoint::moved_distance(int start, int end) {
	Nth nth1 = nth_way(start);
	Nth nth2 = nth_way(end);
	int distance = 0;
	for(int i = nth1.n; i <= nth2.n; i++) {
		distance += waypoints[i].speed * waypoints[i].duration;
	}
	distance -= waypoints[nth1.n].speed * nth1.sec;
	distance -= waypoints[nth2.n].speed * (waypoints[nth2.n].duration - nth2.sec);
	return distance;
}

Nth Waypoint::nth_way(int time) {
	int i, t;
	for(i=0; time > 0; i++) {
		t = time;
		time -= waypoints[i].duration;
	}
	Nth nth;
	nth.n = i;
	nth.sec = t;
	return nth;
}

int Waypoint::how_long_can_i_go(int start, int fuel) {
	Nth nth = nth_way(start);
	int tmp = fuel;
	int dur;
	fuel -= waypoints[nth.n].speed * (waypoints[nth.n].duration - nth.sec);
	while(fuel > 0) {
		tmp = fuel;
		dur += waypoints[nth.n].duration;
		fuel -= waypoints[++nth.n].duration * waypoints[nth.n].speed;
	}
	dur += tmp / waypoints[nth.n].speed;
	return start + dur;
}

int Waypoint::insert_waypoint(Point<int> turn, int spd, int dur)
{
	int i;
	for(i = 0; i < MAX_Waypoints; i++) {
		if(waypoints[i].duration == 0) break;
	}
	if(i < MAX_Waypoints) {
		waypoints[i].speed = spd;
		waypoints[i].turn_center = turn;
		waypoints[i].duration = dur;
		waypoints[i+1] = waypoints[i];
		waypoints[i+1].time_pass(dur);//duration = 0 이 됨.
	} else printf("Way points limit reached!!");
	return i;
}

int Waypoint::delete_waypoint()
{
	int i;
	for(i = 0; i <= MAX_Waypoints; i++) {
		if(waypoints[i].duration == 0) break;
	}
	if(i == 0) printf("No waypoint!!");
	else waypoints[--i].duration = 0;
	return i;
}


