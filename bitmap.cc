#include <stdio.h>
#include <cmath>
#include "point.hpp"
#include "bitmap.h"

Clip::Clip(Point<int> p, int w, int h)
{
	int rest = p.x % 32;
	p.x = p.x - rest;
	this->lower_left = p;
	width =((w + rest) / 32 + 1) * 32;
	height = h;
	
	//memory allocation
	clip = new size_t*[height];
	for(int y = 0; y < height; y++) {
		clip[y] = new size_t[width/32];
	}
}

Clip::Clip(Point<int> c, int r)
{
	c.x -= r;
	c.y -= r;
	Clip* tmp = new Clip(c, (2*r+1)/32, 2*r+1);
	*this = *tmp;
	delete tmp;
}


Clip::Clip(Clip &cl, Point<int> c, int r)
{
	Clip* tmp = new Clip(c, r);
	*this = *tmp;
	delete tmp;
	//copy to clip
	for(int y = 0; y <= height; y++) {
		for(int x = 0; x <= width; x++) {
			if(cl.lower_left.y + y >= 0 && cl.lower_left.x + x >= 0 
					&& cl.lower_left.x + x < width && cl.lower_left.y + y < height) 
				clip[y][x] = cl.clip[y + cl.lower_left.y][x + cl.lower_left.x]; 
		}
	}
}

int Clip::operator = (Clip& cl)
{
	for(int y=0; y<height; y++) delete clip[y];
	delete clip;
	lower_left = cl.lower_left;
	width = cl.width;
	height = cl.height;

	clip = new size_t*[height];
	for(int y=0; y<height; y++) {
		clip[y] = new size_t[width];
		for(int x=0; x<width; x++) {
			clip[y][x] = cl.clip[y][x];
		}
	}
}

Clip::~Clip() 
{
	for(int y = 0; y < height; y++) {
		delete [] clip[y];
	}
	delete [] clip;
}

void Clip::clear()
{
	for(int y=0; y<height; y++) {
		for(int x=0; x<width; x++) {
			clip[y][x] = 0;
		}
	}
}

bool Clip::get_pixel(Point<int> p)
{
	int shift = 32 - 1 - (p.x % 32);
	size_t mask = 1 << shift;
	return clip[p.y][p.x/32] & mask;
}

bool Clip::boundary_check(Point<int> p)
{
	if(p.x < lower_left.x || p.y < lower_left.y) return false;
	if(p.x >= lower_left.x + width || p.y >= lower_left.y + height) return false;
	return true;
}

bool Clip::set_pixel(Point<int> p, bool o)
{
	if(boundary_check(p)) {
		int shift = 32 - 1 - (p.x % 32);
		size_t mask = 1 << shift;
		mask = ~mask;
		size_t t = clip[p.y][p.x/32];
		t = t & mask;
		o = o << shift;
		t = t | o;
		clip[p.y][p.x/32] = t;
		return true;
	} else return false;
}

int Clip::flat_line(Point<int> s, int l)
{
	//boundary check
	if(s.y < 0 || s.y >= height || l <= 0) return -1;
	if(s.x < 0) s.x = 0;
	if(s.x + l >= width) l = width - s.x;
	
	//use coordinate of clip
	unsigned int mask;
	int rest = s.x % 32;
	if(l < 32 - rest) {
		mask = 0xffffffff << (32 - l);
		mask = mask >> rest;
		clip[s.y][s.x / 32] = mask;
	} else {
		mask = 0xffffffff >> rest;
		clip[s.y][s.x / 32] = mask;
		l -= 32 - rest;//앞에서 쓴 부분의 비트맵을 뺀다.
		rest = l % 32;
		int i;
		for(i=1; i <= l/32; i++) clip[s.y][s.x / 32 + i] = 0xffffffff;
		mask = 0xffffffff << (32 - rest);
		clip[s.y][s.x / 32 + i] = mask;
	}
	return l / 32;
}

Point<int> Clip::bit_circle(Point<int> c, int r)
{
	c.x -= 32 * lower_left.x;
	c.y -= lower_left.y;
	Point<int> s;
	for(s.y = c.y - r; s.y <= c.y + r; s.y++) {
		s.x = c.x - sqrtf(r*r - (c.y-s.y)*(c.y-s.y));
		flat_line(s, 2*(s.x-c.x) +1);
	}
	return c;
}

float Clip::bit_line(Point<int> c, float theta)//if theta is over PI, right area of  the line
{
	while(theta > 2 * M_PI) theta -= 2*M_PI;
	while(theta < 0 ) theta += 2*M_PI;
	c.x -= lower_left.x;
	c.y -= lower_left.y;
	float tan = tanf(theta);
	int l;
	for(int y = 0; y < lower_left.y; y++) {
		l = c.x - (y - c.y) / tan;
		if(theta < M_PI) {
			c.x = 0;
			flat_line(c, l);
		} else {
			c.x = l;
			flat_line(c, width - l);
		}
	}
	return tan;
}

Point<int> Clip::bit_arc(Point<int> c, float fr, float to)
{
	c.x -= lower_left.x;
	c.y -= lower_left.y;
	bit_line(c, fr);
	Clip *cl1 = new Clip(lower_left, width, height);
	cl1->bit_line(c, correct_angle(to + M_PI));
	if(to < fr) to += 2 * M_PI;//한바퀴 도는 경우 고려
	if(to - fr < M_PI) paste_from(cl1, AND);
	else paste_from(cl1, OR);
	delete cl1;
	return c;
}

float Clip::bit_arc_line(Point<int> c, int r, float af, float at)
{
	Point<int> p;
	for(;af<=at; af += 1/r) {
		p.x = cosf(af) + c.x;
		p.y = sinf(af) + c.y;
		set_pixel(p, true);
	}
	return r * (at - af);//return arc length
}

Point<int> Clip::bit_arc_circle(Point<int> c, int rf, int rt, float af, float at)
{
	c.x -= lower_left.x;
	c.y -= lower_left.y;
	bit_circle(c, rt);
	Clip *cl1 = new Clip(lower_left, width, height);
	Clip *cl2 = new Clip(lower_left, width, height);
	cl1->bit_circle(c, rf);
	cl2->bit_arc(c, af, at);
	paste_from(cl1, MINUS);
	paste_from(cl2, AND);
	delete cl1;
	delete cl2;
	return c;
}

Clip::Clip(Clip &cl1, Clip &cl2, bitOpion op)//join two into one
{	
	//new clip region to include both clips
	int x = min(cl1.lower_left.x, cl2.lower_left.x);
	int y = min(cl1.lower_left.y, cl2.lower_left.y);
	int width = max(cl1.lower_left.x + cl1.width, cl2.lower_left.x + cl2.width) - cl.lower_left.x;
	width = cl.width / 32;
	int height = max(cl1.lower_left.y + cl1.height, cl2.lower_left.y + cl2.height) - cl.lower_left.y;
	Point<int> p; p.x = x; p.y = y;
	this = new Clip(p, width, height);
	paste_from(cl1, SUBST);
	paste_from(cl2, op);
}

int Clip::paste_from(Clip *source, bitOption op)
{
	int diffx = source->x - lower_left.x;
	int diffy = source->y - lower_left.y;
	for(int y = 0; y <= source->height; y++) {
		if(diffy + y >= 0 && diffy + y < height) {
			for(int x = 0; x <= source->width; x++) {
				if(diffx + x >= 0 && diffx + x < width) {
                    switch(op) {
						case SUBST:
							clip[y + diffy][x + diffx] = source->clip[y][x];
                            break;
						case OR:
							clip[y + diffy][x + diffx] = 
							clip[y + diffy][x + diffx] | source->clip[y][x]; 
							break;
						case AND:
							clip[y + diffy][x + diffx] = 
							clip[y + diffy][x + diffx] & source->clip[y][x];
							break;
						case XOR:
							clip[y + diffy][x + diffx] = 
							clip[y + diffy][x + diffx] ^ source->clip[y][x];
							break;
						case MINUS:
							clip[y + diffy][x + diffx] = 
							clip[y + diffy][x + diffx] & ~source->clip[y][x];
							break;
						case NOT:
							clip[y + diffy][x + diffx] = ~source->clip[y][x];
							break;
					}
				}
			}
		}
	}
	return diffx * diffy;
}

float Clip::correct_angle(float th)
{
	while(th > 2 * M_PI) th -= 2 * M_PI;
	while(th < 0) th += 2 * M_PI;
	return th;
}

Bitmap::Bitmap(int w, int h, int bpp) : Clip(z, w, h)
{
	bit_per_pixel = bpp;
	for(int i=0; i<bpp; i++) bitmap[i] = new Clip(this);
}


int Bitmap::get_pixel(Point<int> p)
{
	int b;
	for(int i=0; i<bit_per_pixel; i++) {
		b = bitmap[i]->get_pixel(p);
		b = b >> shift;
		ret += b << i;
	}
	return ret;
}

void Bitmap::set_pixel(Point<int> p, unsigned char v)
{
	bool t;
	for(int i=0; i<bit_per_pixel; i++) {
		t = (v >> i) & 1;
		bitmap[i]->set_pixel(p, t);
	}
}



