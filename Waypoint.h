#pragma once
#include <vector>
#include "point.hpp"

class Nth 
{
public:
	int n;
	int sec;
	int fuel_usage;
	bool operator<(Nth nth);
};

class WhereAbout : public Point
{
public:
	WhereAbout() {}
	WhereAbout(Point position, float heading, int turning = 0, int speed = 0, int duration = 0);
	
	//main function of this class. return left duration, change members
	virtual int time_pass(int time, float penalty = 1);

	void operator = (WhereAbout& wh);
	void save();
	void restore();

	//getter
	void set_turning(int turning);
	int get_turning() {return turning;}
	Point get_turn_center() {return turn_center;}

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
	int insert_waypoint(int turning, int spd, int dur, float penalty);//return inserted nth waypoint
	void delete_waypoint() {waypoints.pop_back();}
	Nth nth_way(int time, int fuel);//time in at which waypoint & moment
	//void operator = (WhereAbout<float> &wh) {*this = wh;}

protected:
	int moved_distance(int start_time, int end_time);
	int how_long_can_i_go(int start_time, int remainning_fuel);//return maximum time 

private:
	
};

