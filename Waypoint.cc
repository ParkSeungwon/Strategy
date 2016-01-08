#include <typeinfo>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "Waypoint.h"
#include "Util.h"
using namespace std;

template <class T> 
float WhereAbout<T>::correct_angle(float f)
{
	while(f >= M_PI) f -= M_PI;
	while(f < 0) f += M_PI;
	return f;
}

template <class T> 
int WhereAbout<T>::time_pass(int time, float penalty)
{//change position & duration according to turncenter, duration, heading
//	if(duration == 0) return *this;
	if(time > duration) time = duration;
	float r = position ^ turn_center;
	float center_angle = position % turn_center;
	if(position.y > 0) center_angle += M_PI; //현 위치에서 센터로 가는 벡터의 각도
	float theta = speed * time * penalty/ r;//moved angle affected by penalty
	
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
	this->penalty = penalty;
	return duration;
}

template <class T> template <typename T2>
void WhereAbout<T>::operator = (WhereAbout<T2> &wh)
{
	position = wh.position;
	turn_center = wh.turn_center;
	speed = wh.speed;
	heading_toward = wh.heading_toward;
	duration = (T)wh.duration;
}

template <class T> 
void WhereAbout<T>::save()
{
	save_pos = position;
	save_tc = turn_center;
	save_speed = speed;
	save_head = heading_toward;
	save_dur = duration;
	save_penalty = penalty;
}

template <class T> 
void WhereAbout<T>::restore()
{
	position = save_pos;
	turn_center = save_tc;
	speed = save_speed;
	heading_toward = save_head;
	duration = save_dur;
	penalty = save_penalty;
}

int Waypoint::nth_way(int time) {
	int i, t;
	for(i=0; time > 0; i++) {
		t = time;
		time -= waypoints[i].duration;
	}
	(WhereAbout)*this = waypoints[i];
	return t;
}

int Waypoint::insert_waypoint(Point<int> turn, int spd, int dur, float p)
{
	int ret = waypoints.size();
	WhereAbout<int> mediator;
	if(ret == 0) {//if none push current position
		mediator = *this;
		waypoints.push_back(mediator);
		ret++;
	}

	vector<WhereAbout<int> >::iterator it = waypoints.end();
	it--;
	it->save();
	it->time_pass(it->duration, it->penalty);
	mediator = *it;//reuse mediator, change position
	it->restore();
	mediator.speed = spd;
	mediator.turn_center = turn;
	mediator.duration = dur;
	mediator.penalty = p;
	waypoints.push_back(mediator);

	return ret + 1;//size of waypoints
}

