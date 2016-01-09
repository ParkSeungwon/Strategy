#include <typeinfo>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "Waypoint.h"
#include "Util.h"
using namespace std;

WhereAbout::WhereAbout(Point p, float h, int t, int s, int d)
{
	heading_toward = h;
	x = p.x;
	y = p.y;
	speed = s;
	duration = d;
	set_turning(t);
}

WhereAbout::set_turning(int t)
{
	turning = t;
	if(t == 0) turn_center = *this;
	else {
		int i = t > 0 ? 1 : -1;
		turn_center.x = abs(t) * cosf(heading_toward - i * M_PI/2) + x;
		turn_center.y = abs(t) * sinf(heading_toward - i * M_PI/2) + y;
	}
}

float WhereAbout::correct_angle(float f)
{
	while(f >= 2*M_PI) f -= 2*M_PI;
	while(f < 0) f += 2*M_PI;
	return f;
}

int WhereAbout::time_pass(int time, float penalty)
{//change position & duration according to turncenter, duration, heading
//	if(duration == 0) return *this;
	if(time > duration) time = duration;
	int r = abs(turning);
	float center_angle = position % turn_center;
	if(position.y > 0) center_angle += M_PI; //현 위치에서 센터로 가는 벡터의 각도
	float theta = speed * time * penalty/ r;//moved angle affected by penalty
	
	float diff = abs(center_angle - correct_angle(heading_toward + M_PI/2));
	if(turning == 0) {//go straight
		x += r * cosf(heading_toward);
		y += r * sinf(heading_toward);
	} else if(turning < 0) { //if center is at the left of heading direction
		heading_toward += theta;
		x = turn_center.x + r * cosf(center_angle + theta);
		y = turn_center.y + r * sinf(center_angle + theta);
	} else {
		heading_toward -= theta;
		x = turn_center.x + r * cosf(center_angle - theta);
		y = turn_center.y + r * sinf(center_angle - theta);
	}
	duration -= time;//left duration of this waypiont
	this->penalty = penalty;
	return duration;
}

void WhereAbout::operator = (WhereAbout &wh)
{
	x = wh.x; 
	y = wh.y;
	turn_center = wh.turn_center;
	speed = wh.speed;
	heading_toward = wh.heading_toward;
	duration = wh.duration;
}

void WhereAbout::save()
{
	save_pos = position;
	save_tc = turn_center;
	save_speed = speed;
	save_head = heading_toward;
	save_dur = duration;
	save_penalty = penalty;
}

void WhereAbout::restore()
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

int Waypoint::insert_waypoint(Point turn, int spd, int dur, float p)
{
	int ret = waypoints.size();
	WhereAbout mediator;
	if(ret == 0) {//if none push current position
		mediator = *this;
		waypoints.push_back(mediator);
		ret++;
	}

	vector<WhereAbout>::iterator it = waypoints.end();
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

