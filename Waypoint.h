#pragma once
#include <vector>
#include "point.hpp"

template <class T = int> 
class WhereAbout
{
public:
	Point<T> position, turn_center;
	int speed;
	float heading_toward;
	int duration;//how long will this keep on going like this
	float penalty;// to store in waypoint

	virtual int time_pass(int time, float penalty = 1);	//return left duration, change members
	//지형의 영향력을 고려한다. 호를 100개 내지 일정한 개수의 점으로 나누어서 각 점의 지형을 샘플로 뽑아 속도를 계산한다.
	template <typename T2> void operator = (WhereAbout<T2> &wh);
	void save();
	void restore();

protected:
	float correct_angle(float);

private:
	Point<T> save_pos, save_tc;
	int save_speed;
	float save_head;
	int save_dur;
};

class Waypoint : public WhereAbout<>
{
public:
	std::vector<WhereAbout<int> > waypoints;//last array for storing init value
	int insert_waypoint(Point<int> turn, int spd, int dur, float penalty);//return inserted nth waypoint
	void delete_waypoint() {waypoints.pop_back();}
	int nth_way(int time);//time in at which waypoint & moment
	//void operator = (WhereAbout<float> &wh) {*this = wh;}

protected:
	int moved_distance(int start_time, int end_time);
	int how_long_can_i_go(int start_time, int remainning_fuel);//return maximum time 

private:
	
};

