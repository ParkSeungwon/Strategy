#include "point.hpp"
#include <cmath>

template <class T> Point<T> Point<T>::polar_to_xy(T r, float th)
{
	Point<T> p;
	p.x = cosf(th) * r;
	p.y = sinf(th) * r;
	return p;
}

template <class T> Point<int> Point<T>::to_int()
{
	Point<int> ret;
	ret = *this;
	return ret;
}

template <class T> Point<float> Point<T>::to_float()
{
	Point<float> ret;
	ret = *this;
	return ret;
}
