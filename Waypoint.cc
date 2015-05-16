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
