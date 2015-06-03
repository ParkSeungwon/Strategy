#include <typeinfo>
#include <cmath>
#include "Waypoint.h"
#include "Util.h"

float WhereAbout::correct_angle(float f)
{
	while(f >= M_PI) f -= M_PI;
	while(f < 0) f += M_PI;
	return f;
}

WhereAbout WhereAbout::time_pass(int time)
{
//	if(duration == 0) return *this;
	WhereAbout wh;
	int rt = 0;
	if(time > duration) time = duration;
	float x = position.x - turn_center.x;
	float y = position.y - turn_center.y;
	float r = sqrtf(x*x + y*y);
	float center_angle = acosf(x/r);
	if(y > 0) center_angle += M_PI; //현 위치에서 센터로 가는 벡터의 각도
	float theta = speed * time / r;
	
	float diff = abs(center_angle - correct_angle(initial_heading_toward + M_PI/2));
	if(diff < 0.1 || diff > 3) { //if center is at the left of heading direction
		wh.heading_toward = heading_toward + theta;
		wh.position.x = turn_center.x + r * cosf(center_angle + theta);
		wh.position.y = turn_center.y + r * sinf(center_angle + theta);
	} else {
		wh.heading_toward = initial_heading_toward - theta;
		wh.position.x = turn_center.x + r * cosf(center_angle - theta);
		wh.position.y = turn_center.y + r * sinf(center_angle - theta);
	}
	wh.speed = speed;
	wh.turn_center = turn_center;
	wh.duration = duration - time;//left duration of this waypiont
	return wh;
}

WhereAbout Waypoint::time_pass(int time)
{
	int i, t;
	for(i=0, time > 0; i++) {
		t = time;
		time -= waypoints[i].duration;
	}
	return waypoints[i].time_pass[time];
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
	for(i=0, time > 0; i++) {
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

int Waypoint::insert_waypoint(CGPoint turn, int spd, int dur)
{
	int i;
	for(i = 0; i < MAX_Waypoints; i++) {
		if(waypoints[i].duration == 0) break;
	}
	if(i < MAX_Waypoints) {
		waypoints[i].speed = spd;
		waypoints[i].turn_center = turn;
		waypoints[i].duration = dur;
		waypoints[i+1] = waypoints[i].time_pass(dur);//reach here by this waypoint
		waypoints[i+1].duration = 0;//work as a mark
	} else message("Way points limit reached!!");
	return i;
}

int Waypoint::delete_waypoint()
{
	int i;
	for(i = 0; i <= MAX_Waypoints; i++) {
		if(waypoints[i].duration == 0) break;
	}
	if(i == 0) message("No waypoint!!")
	else waypoints[--i].duration = 0;
	return i;
}

