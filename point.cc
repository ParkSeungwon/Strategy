#include "point.h"
#include <cmath>
#include <complex>

Point Point::polar_to_xy(int r, float th)
{
	Point p;
	p.x = cosf(th) * r;
	p.y = sinf(th) * r;
	return p;
}

float Point::operator^(Point p) const//distance 
{
	return sqrtf((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

float Point::operator%(Point p) const//angle to p
{
	std::complex<float> c(p.x-x, p.y-y);
	return std::arg(c);
}


Point Point::operator = (Point p)
{
	x = p.x;
	y = p.y;
	return *this;
}

Point Point::operator-(Point p) const
{
	Point p2;
	p2.x = x - p.x;
	p2.y = y - p.y;
	return p2;
}

Point Point::operator+(Point p) const
{
	Point p2;
	p2.x = x + p.x;
	p2.y = y + p.y;
	return p2;
}
