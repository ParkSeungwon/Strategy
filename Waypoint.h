#define MAX_Waypoints 10

struct CGPoint {
	float x,y;
};

struct Nth {
	int n, sec;
}

class WhereAbout
{
public:
	CGPoint position, turn_center;
	int speed, duration;

	virtual WhereAbout time_pass(int time);	//return class not ref.	
	
	void set_headingToward(float f) {headingToward = correct_angle(f)}
	float get_headingToward() {return headingToward;}
	
private:
	float correct_angle(float);
	float heading_toward;
};

class Waypoint
{
public:
	WhereAbout waypoints[MAX_Waypoints + 1];//last array for storing init value
	
	WhereAbout time_pass(int time);//return nth waypoint, and construct the data of it
	int moved_distance(int start_time, int end_time);
	int how_long_can_i_go(int start_time, int remainning_fuel);
	int insert_waypoint(CGPoint turn, int spd, int dur);//return inserted nth waypoint
	int delete_waypoint();
	Nth nth_way(int time);//time in at which waypoint & moment
private:
	
};
