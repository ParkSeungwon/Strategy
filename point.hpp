#pragma once

template <class T> class Point 
{
public:
	T x,y;
	Point();
	Point(T x, T y) {this->x = x; this->y = y;}
	float operator ^ (Point<T> p) const; //distance
	float operator % (Point<T> p) const {return atanf((p.y - y) / (p.x - x));}//angle
	void operator = (Point<int> p) {x = (T)p.x; y = (T)p.y;}
	void operator = (Point<float> p) {x = (T)p.x; y = (T)p.y;}
	Point<T> operator - (Point<T> p) const;
	Point<T> operator + (Point<T> p) const;
	void operator += (Point<T> p) {x += p.x; y += p.y;}
	void operator -= (Point<T> p) {x -= p.x; y -= p.y;}
	Point<int> to_int();
	Point<float> to_float();
	Point<T> polar_to_xy(T r, float theta);
};

