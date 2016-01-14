#include <typeinfo>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "Waypoint.h"
#include "Util.h"
using namespace std;
using namespace Glob;

WhereAbout::WhereAbout(Point p, float h, int t, int s, int d)
{
	heading_toward = h;
	x = p.x;
	y = p.y;
	speed = s;
	duration = d;
	set_turning(t);
}

void WhereAbout::set_turning(int t)
{
	turning = t;
	if(t == 0) turn_center = *this;
	else {
		int i = t > 0 ? 1 : -1;
		turn_center.x = t * i * cosf(heading_toward - i * M_PI/2) + x;
		turn_center.y = t * i * sinf(heading_toward - i * M_PI/2) + y;
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
	int i = turning > 0 ? 1 : -1;
	int r = turning * i;//abs
	float center_angle = correct_angle(heading_toward - i * M_PI / 2);//O = x,y
	center_angle = correct_angle(center_angle + M_PI);//O = turn center
	float theta = speed * time * penalty / r;//moved angle affected by penalty
	
	if(turning == 0) {//go straight
		float f = Point(0,0) ^ Point(1,1);//root2
		f = speed * time * penalty / f;
		x += f * cosf(heading_toward);
		y += f * sinf(heading_toward);
	} else { //if center is at the left or right of heading direction
		heading_toward -= i * theta;
		x = turn_center.x + r * cosf(center_angle - i * theta);
		y = turn_center.y + r * sinf(center_angle - i * theta);
	}
//	duration -= time;//left duration of this waypiont
	this->penalty = penalty;
	return speed * time;//fuel usage
}

void WhereAbout::operator = (WhereAbout &wh)
{
	x = wh.x; 
	y = wh.y;
	turning = wh.turning;
	turn_center = wh.turn_center;
	speed = wh.speed;
	heading_toward = wh.heading_toward;
	duration = wh.duration;
}

void WhereAbout::save()
{
	save_pos.x = x; save_pos.y = y;
	save_tc = turn_center;
	save_speed = speed;
	save_head = heading_toward;
	save_dur = duration;
	save_penalty = penalty;
	save_turning = turning;
}

void WhereAbout::restore()
{
	x = save_pos.x; y = save_pos.y;
	turn_center = save_tc;
	speed = save_speed;
	heading_toward = save_head;
	duration = save_dur;
	penalty = save_penalty;
	turning = save_turning;
}

int Waypoint::insert_waypoint(int turning, int spd, int dur, float p)
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
	mediator.set_turning(turning);
	mediator.duration = dur;
	mediator.penalty = p;
	waypoints.push_back(mediator);

	return ret + 1;//size of waypoints
}

int Waypoint::time_pass(float penalty)
{
	(WhereAbout)*this = waypoints[cur_waypt];
	cur_time_in_waypt += OneTick;
	WhereAbout::time_pass(cur_time_in_waypt, penalty);
	if(cur_time_in_waypt == waypoints[cur_waypt].duration) {
		cur_waypt++;
		cur_time_in_waypt = 0;
	}
	return cur_waypt;
}

