#pragma once

template <class T> class Point {
public:
	T x,y;
	Point();
	Point(T _x, T _y) {x = _x; y = _y;}
	float operator - (Point<T> b) {return sqrtf((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));}//distance 
	float operator % (Point<T> a) {return atanf((a.y - y) / (a.x - x));}//angle
	void operator = (Point<int> p) {x = (T)p.x; y = (T)p.y;}
	void operator = (Point<float> p) {x = (T)p.x; y = (T)p.y;}
	void operator + (int i) {x += i; y += i;}
	void operator - (int i) {x -= i; y =- i;}
	Point<int> to_int();
	Point<float> to_float();
	Point<T> polar_to_xy(T r, float theta);
};

