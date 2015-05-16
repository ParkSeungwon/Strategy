struct CGPoint {
	float x,y;
};

class WhereAbout
{
	public:
		CGPoint position;
		CGPoint turnCenter;
		float headingToward;
		int speed;
};

class Waypoint : public WhereAbout 
{
	public:
		int duration;		//second 모든 지속의 합은 1턴이 됨.
		float radius;
		Waypoint(Waypoint &prev, int _duration, int _speed, CGPoint _turnCenter);
		WhereAbout *where(int when);
		
};
