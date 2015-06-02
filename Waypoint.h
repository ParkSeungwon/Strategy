#define MAX_Waypoints 10

struct CGPoint {
	float x,y;
};

class WhereAbout
{
public:
	virtual int time_pass(int time);	//return unused time
	CGPoint initial_position, position;
	CGPoint turn_center;
	int speed;
	int duration;
	
	void set_headingToward(float f) {headingToward = correct_angle(f)}
	float get_headingToward() {return headingToward;}
	
private:
	float correct_angle(float);
	float initial_heading_toward, heading_toward;
};

class Waypoint : public WhereAbout 
{
public:
	WhereAbout waypoints[MAX_Waypoints];
	int duration;		//second 모든 지속의 합은 1턴이 됨.
	float radius;
	Waypoint(Waypoint &prev, int _duration, int _speed, CGPoint _turnCenter);
	WhereAbout *where(int when);
		
};
