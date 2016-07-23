#pragma once
#include <vector>
#include "point.h"

class WhereAbout : public Point
{
public:
	WhereAbout() {}
	WhereAbout(Point position, float heading, int turning = 0, int speed = 0, int duration = 0);
	
	//main function of this class. return left duration, change members
	virtual int time_pass(int time, float penalty = 1);

	WhereAbout& operator=(WhereAbout& wh);
	void save();
	void restore();

	//getter
	void set_turning(int turning);
	int get_turning() const{return turning;}
	Point get_turn_center() const {return turn_center;}

	//member variables
	int speed;
	int duration;//how long will it keep on going like this
	float heading_toward;
	float penalty;// to store in waypoint

protected:
	float correct_angle(float);
	int turning; //if 0 straight, + right, - left
	Point turn_center;

private://for saving status temporarily
	Point save_pos, save_tc;
	int save_speed, save_dur, save_turning;
	float save_head, save_penalty;
};

class Waypoint : public WhereAbout
{
public:
	std::vector<WhereAbout> waypoints;
	int insert_waypoint(int turning, int spd, int dur, float penalty = 1);//return inserted nth waypoint
	void delete_waypoint() {waypoints.pop_back();}
	int time_pass(float penalty = 1);
	//void operator = (WhereAbout<float> &wh) {*this = wh;}

	int get_cur_waypt() {return cur_waypt;}
	int get_cur_time_in_waypt() {return cur_time_in_waypt;}

protected:
	int cur_waypt=0, cur_time_in_waypt=0;
	int moved_distance(int start_time, int end_time);
	int how_long_can_i_go(int start_time, int remainning_fuel);//return maximum time 

private:
	
};

