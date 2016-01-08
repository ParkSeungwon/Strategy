#pragma once
#include <vector>
#include "point.hpp"

template <class T = int> 
class WhereAbout
{
public:
	//main function of this class. return left duration, change members
	virtual int time_pass(int time, float penalty = 1);

	template <typename T2> void operator = (WhereAbout<T2> &wh);
	void save();
	void restore();

	Point<T> position, turn_center;
	int speed;
	int duration;//how long will it keep on going like this
	float heading_toward;
	float penalty;// to store in waypoint

protected:
	float correct_angle(float);

private://for saving status temporarily
	Point<T> save_pos, save_tc;
	int save_speed, save_dur;
	float save_head, save_penalty;
};

class Waypoint : public WhereAbout<>
{
public:
	std::vector<WhereAbout<int> > waypoints;
	int insert_waypoint(Point<int> turn, int spd, int dur, float penalty);//return inserted nth waypoint
	void delete_waypoint() {waypoints.pop_back();}
	int nth_way(int time);//time in at which waypoint & moment
	//void operator = (WhereAbout<float> &wh) {*this = wh;}

protected:
	int moved_distance(int start_time, int end_time);
	int how_long_can_i_go(int start_time, int remainning_fuel);//return maximum time 

private:
	
};

