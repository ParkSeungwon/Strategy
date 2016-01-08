#pragma once

template <class T> class Point 
{
public:
	T x,y;
	Point();
	Point(T x, T y) {this->x = x; this->y = y;}

	float operator ^ (Point<T> p) const; //distance
	float operator % (Point<T> p) const {return atanf((p.y - y) / (p.x - x));}//angle
	template <typename T2> Point<T> operator = (Point<T2> p);
	Point<T> operator - (Point<T> p) const;
	Point<T> operator + (Point<T> p) const;
	void operator += (Point<T> p) {x += p.x; y += p.y;}
	void operator -= (Point<T> p) {x -= p.x; y -= p.y;}

	Point<int> to_int() const;
	Point<float> to_float() const;
	Point<T> polar_to_xy(T r, float theta);
};

