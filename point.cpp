#include "point.hpp"
#include <cmath>

template <class T> Point<T> Point<T>::polar_to_xy(T r, float th)
{
	Point<T> p;
	p.x = cosf(th) * r;
	p.y = sinf(th) * r;
	return p;
}

