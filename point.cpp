#include "point.hpp"
#include <cmath>

template <class T> 
Point<T> Point<T>::polar_to_xy(T r, float th)
{
	Point<T> p;
	p.x = cosf(th) * r;
	p.y = sinf(th) * r;
	return p;
}

template <class T> 
float Point<T>::operator^(Point<T> p) const//distance 
{
	return sqrtf((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

template <class T> template <typename T2>
Point<T> Point<T>::operator = (Point<T2> p)
{
	x = (T)p.x;
	y = (T)p.y;
	return *this;
}

template <class T> 
Point<int> Point<T>::to_int() const
{
	Point<int> ret;
	ret = *this;
	return ret;
}

template <class T> 
Point<float> Point<T>::to_float() const
{
	Point<float> ret;
	ret = *this;
	return ret;
}

template <class T> 
Point<T> Point<T>::operator-(Point<T> p) const
{
	Point<T> p2;
	p2.x = x - p.x;
	p2.y = y - p.y;
	return p2;
}

template <class T> 
Point<T> Point<T>::operator+(Point<T> p) const
{
	Point<T> p2;
	p2.x = x - p.x;
	p2.y = y - p.y;
	return p2;
}
