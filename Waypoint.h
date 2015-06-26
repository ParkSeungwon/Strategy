#define MAX_Waypoints 10

struct Nth {
	int n, sec;
};

template <class T = int> struct Point {
	T x,y;
};

template <class T = int> class WhereAbout
{
public:
	Point<T> position, turn_center;
	int speed;
	T duration;

	virtual WhereAbout time_pass(T time);	//return class not ref.	
	//지형의 영향력을 고려한다. 호를 100개 내지 일정한 개수의 점으로 나누어서 각 점의 지형을 샘플로 뽑아 속도를 계산한다.
	void set_headingToward(float f) {heading_toward = correct_angle(f);}
	float get_headingToward() {return heading_toward;}

protected:
	float distance_between(Point<T> a, Point<T> b);
	float angle(Point<T> center, Point<T> a);
	Point<T> polar_to_xy(T radius, float theta);

private:
	float correct_angle(float);
	float heading_toward;
};

template <class T = int> class Waypoint : public WhereAbout<T>
{
public:
	WhereAbout<int> waypoints[MAX_Waypoints + 1];//last array for storing init value
	
	WhereAbout<T> time_pass(T time);//return nth waypoint, and construct the data of it
	int moved_distance(int start_time, int end_time);
	int how_long_can_i_go(int start_time, int remainning_fuel);//return maximum time 
	int insert_waypoint(Point<T> turn, int spd, int dur);//return inserted nth waypoint
	int delete_waypoint();
	Nth nth_way(T time);//time in at which waypoint & moment
private:
	
};
