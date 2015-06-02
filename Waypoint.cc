#include <typeinfo>
#include <cmath>
#include "Waypoint.h"
#include "Util.h"

Waypoint::Waypoint(Waypoint &prev, int _duration, int _speed, CGPoint _turnCenter)
{
	if (_duration <= 0) throw 1;
	
    duration = _duration;
	speed = _speed;
	turnCenter = _turnCenter;
	if (typeid(prev).name() == "WhereAbout") {			//첫번째 경로일 경우 
		position = prev.position;
		headingToward = prev.headingToward;
	}  	
	else {
		float theta = prev.speed * prev.duration / prev.radius;
		position.x = prev.turnCenter.x + prev.radius * cosf(theta + prev.headingToward - M_PI/2);
	  	position.y = prev.turnCenter.y + prev.radius * sinf(theta + prev.headingToward - M_PI/2);
  		headingToward = prev.headingToward + theta;
	}
	radius = Util::distanceBetween(turnCenter, position);
}

WhereAbout::WhereAbout(int )
WhereAbout* Waypoint::where(int when) 
{
	if(when>duration) throw 5;
	WhereAbout *ptr = new WhereAbout;
	float theta = speed * when / radius;
	ptr->position.x = turnCenter.x + radius * cosf(theta + headingToward - M_PI/2);
	ptr->position.y = turnCenter.y + radius * sinf(theta + headingToward - M_PI/2);  
	ptr->headingToward += theta;			//방향 조절
	ptr->speed = speed;
	return ptr;				
}

float WhereAbout::correct_angle(float f)
{
	while(f >= M_PI) f -= M_PI;
	while(f < 0) f += M_PI;
	return f;
}

int time_pass(int time)
{
	int rt = 0;
	if(time > duration) {
		rt = time - duration;
		time = duration;
	}
	duration -= time;
	float x = initial_position.x - turnCenter.x;
	float y = initial_position.y - turnCenter.y;
	float r = sqrtf(x*x + y*y);
	float center_angle = acosf(x/r);
	if(y/r > 0) center_angle += M_PI; //현 위치에서 센터로 가는 벡터의 각도
	float theta = speed * time / r;
	
	float diff = abs(center_angle - correct_angle(initial_heading_toward + M_PI/2);
	if(diff < 0.1 || diff > 3) {
		heading_toward = initial_heading_toward + theta;
		position.x = turnCenter.x + r * cosf(center_angle + theta);
		position.y = turnCenter.y + r * sinf(center_angle + theta);
	} else {
		heading_toward = initial_heading_toward - theta;
		position.x = turnCenter.x + r * cosf(center_angle - theta);
		position.y = turnCenter.y + r * sinf(center_angle - theta);
	}
	return rt;
}


