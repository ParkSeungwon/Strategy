#define MAX_Waypoints 10

struct FPoint {
	float x,y;
};

struct Nth {
	int n, sec;
}

template <Typename T = int>
class WhereAbout
{
public:
	FPoint position, turn_center;
	int speed;
	T duration;

	virtual WhereAbout time_pass(T time);	//return class not ref.	
	//지형의 영향력을 고려한다. 호를 100개 내지 일정한 개수의 점으로 나누어서 각 점의 지형을 샘플로 뽑아 속도를 계산한다.
	void set_headingToward(float f) {headingToward = correct_angle(f)}
	float get_headingToward() {return headingToward;}

protected:
	float distance_between(IPoint a, IPoint b);
	float angle(IPoint center, IPoint a);
	IPoint polar_to_xy(float radius, float theta);

private:
	float correct_angle(float);
	float heading_toward;
};

class Waypoint : public WhereAbout<T>
{
public:
	WhereAbout waypoints[MAX_Waypoints + 1];//last array for storing init value
	
	WhereAbout time_pass(T time);//return nth waypoint, and construct the data of it
	int moved_distance(int start_time, int end_time);
	int how_long_can_i_go(int start_time, int remainning_fuel);
	int insert_waypoint(CGPoint turn, int spd, int dur);//return inserted nth waypoint
	int delete_waypoint();
	Nth nth_way(T time);//time in at which waypoint & moment
private:
	
};
