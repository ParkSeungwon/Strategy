#define MAX_Waypoints 10

struct Nth {
	int n, sec;
};


template <class T = int> class WhereAbout
{
public:
	Point<T> position, turn_center;
	int speed;
	float heading_toward;
	T duration;//how long will this keep on going like this

	virtual int time_pass(T time);	//return left duration, change members
	//지형의 영향력을 고려한다. 호를 100개 내지 일정한 개수의 점으로 나누어서 각 점의 지형을 샘플로 뽑아 속도를 계산한다.
	int operator = (WhereAbout<int> &wh);

protected:
	float correct_angle(float);

private:
};

class Waypoint : public WhereAbout<float>
{
public:
	WhereAbout<int> waypoints[MAX_Waypoints + 1];//last array for storing init value
	int time_pass(int time);//return nth waypoint, and construct the data of it
	int insert_waypoint(Point<int> turn, int spd, int dur);//return inserted nth waypoint
	int delete_waypoint();
	Nth nth_way(int time);//time in at which waypoint & moment

protected:
	int moved_distance(int start_time, int end_time);
	int how_long_can_i_go(int start_time, int remainning_fuel);//return maximum time 

private:
	
};
