#pragma once

class Point 
{
public:
	int x,y;
	Point();
	Point(int x, int y) {this->x = x; this->y = y;}

	float operator ^ (Point p) const; //distance
	float operator % (Point p) const;
	Point operator = (Point p);
	Point operator - (Point p) const;
	Point operator + (Point p) const;
	void operator += (Point p) {x += p.x; y += p.y;}
	void operator -= (Point p) {x -= p.x; y -= p.y;}

	Point polar_to_xy(int r, float theta);
};

