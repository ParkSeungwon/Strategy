#include <cmath>
#include "bitmap.h"
#include "Util.h"
using namespace Glob;

Clip::Clip(Point p, int w, int h)
{
	size_of_char = sizeof(char);
	if(p.x < 0) {
		w += p.x;
		if(w < 0) w = 0;
		p.x = 0;
	}
	if(p.y < 0) {
		h += p.y;
		if(h < 0) h = 0;
		p.y = 0;
	}
	int rest = p.x % size_of_char;
	p.x = p.x - rest;
	this->lower_left = p;
	width =((w + rest) / size_of_char + 1) * size_of_char;
	height = h;
	
	//memory allocation
	clip = new char*[height];
	for(int y = 0; y < height; y++) {
		clip[y] = new char[width/size_of_char];
	}
}

int Clip::set_lower_left(Point p)
{
	lower_left.y = p.y;
	int rest = p.x % size_of_char;
	lower_left.x = p.x - rest;
	return rest;
}

Clip::Clip(Point c, int r)
{
	c.x -= r;
	c.y -= r;
	*this = Clip(c, 2*r+1, 2*r+1);
}

Clip& Clip::operator=(Clip&& cl)
{
	if(this == &cl) return *this;
	lower_left = cl.lower_left;
	width = cl.width;
	height = cl.height;
	del_clip();
	clip = cl.clip;
	cl.clip = nullptr;
	return *this;
}


Clip::Clip(Clip &cl, Point c, int r)
{
	*this = Clip(c, r);
	int lx = this->lower_left.x;
	int ly = this->lower_left.y;
	int cx = cl.lower_left.x;
	int cy = cl.lower_left.y;
	int wi = cl.width / size_of_char;
	//copy to clip
	for(int y = 0; y <= height; y++) {
		for(int x = 0; x <= width/size_of_char; x++) {
			if(ly + y >= cy && lx + x >= cx && 
					lx + x <= cx + wi && ly + y <= cy + cl.height) 
				clip[y][x] = cl.clip[y + ly - cy][x + lx - cx]; 
		}
	}
}

Clip& Clip::operator = (Clip& cl)
{
	if(this == &cl) return *this;
	del_clip();
	lower_left = cl.lower_left;
	width = cl.width;
	height = cl.height;
	size_of_char = cl.size_of_char;
	clip = new char*[height];
	for(int y=0; y<height; y++) {
		clip[y] = new char[width];
		for(int x=0; x<width; x++) {
			clip[y][x] = cl.clip[y][x];
		}
	}
	return *this;
}

Clip::~Clip() 
{
	del_clip();
}

void  Clip::del_clip()
{
	if(clip != nullptr) {
		for(int y = 0; y < height; y++) {
			delete [] clip[y];
		}
		delete [] clip;
	}
}

void Clip::clear()
{
	for(int y=0; y<height; y++) {
		for(int x=0; x<width/size_of_char; x++) {
			clip[y][x] = 0;
		}
	}
}

bool Clip::get_pixel(Point p)
{
	int shift = size_of_char - 1 - (p.x % size_of_char);
	size_t mask = 1 << shift;
	return clip[p.y][p.x/size_of_char] & mask;
}

bool Clip::boundary_check(Point p)
{
	if(p.x < lower_left.x || p.y < lower_left.y) return false;
	if(p.x >= lower_left.x + width || p.y >= lower_left.y + height) return false;
	return true;
}

bool Clip::set_pixel(Point p, bool o)
{
	if(boundary_check(p)) {
		int shift = size_of_char - 1 - (p.x % size_of_char);
		size_t mask = 1 << shift;
		mask = ~mask;
		size_t t = clip[p.y][p.x/size_of_char];
		t = t & mask;
		o = o << shift;
		t = t | o;
		clip[p.y][p.x/size_of_char] = t;
		return true;
	} else return false;
}

int Clip::flat_line(Point s, int l)
{
	//boundary check
	if(s.y < 0 || s.y >= height || l <= 0) return -1;
	if(s.x < 0) s.x = 0;
	if(s.x + l >= width) l = width - s.x;
	
	//use coordinate of clip
	unsigned int mask;
	int rest = s.x % size_of_char;
	if(l < size_of_char - rest) {
		mask = 0xffffffff << (size_of_char - l);
		mask = mask >> rest;
		clip[s.y][s.x / size_of_char] = mask;
	} else {
		mask = 0xffffffff >> rest;
		clip[s.y][s.x / size_of_char] = mask;
		l -= size_of_char - rest;//앞에서 쓴 부분의 비트맵을 뺀다.
		rest = l % size_of_char;
		int i;
		for(i=1; i <= l/size_of_char; i++) clip[s.y][s.x / size_of_char + i] = 0xffffffff;//error
		mask = 0xffffffff << (size_of_char - rest);
		clip[s.y][s.x / size_of_char + i] = mask;
	}
	return l / size_of_char;
}

Point Clip::bit_circle(Point c, int r)
{
	c.x -= size_of_char * lower_left.x;
	c.y -= lower_left.y;
	Point s;
	for(s.y = c.y - r; s.y <= c.y + r; s.y++) {
		s.x = c.x - sqrtf(r*r - (c.y-s.y)*(c.y-s.y));
		flat_line(s, 2*(s.x-c.x) +1);
	}
	return c;
}

float Clip::bit_line(Point c, float theta)//if theta is over PI, right area of  the line
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

Point Clip::bit_arc(Point c, float fr, float to)
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

float Clip::bit_arc_line(Point c, int r, float af, float at)
{
	Point p;
	for(;af<=at; af += 1/r) {
		p.x = cosf(af) + c.x;
		p.y = sinf(af) + c.y;
		set_pixel(p, true);
	}
	return r * (at - af);//return arc length
}

Point Clip::bit_arc_circle(Point c, int rf, int rt, float af, float at)
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

Clip::Clip(Clip &cl1, Clip &cl2, bit_operation op)//join two into one
{	
	//new clip region to include both clips
	int x = min(cl1.lower_left.x, cl2.lower_left.x);
	int y = min(cl1.lower_left.y, cl2.lower_left.y);
	int width = max(cl1.lower_left.x + cl1.width, cl2.lower_left.x + cl2.width) - x;
	int height = max(cl1.lower_left.y + cl1.height, cl2.lower_left.y + cl2.height) - y;
	Clip* cl = new Clip(Point(x, y), width, height);
	*this = *cl;
	delete cl;
	paste_from(&cl1, SUBST);
	paste_from(&cl2, op);
}

int Clip::paste_from(Clip *source, bit_operation op)
{
	int diffx = source->lower_left.x - lower_left.x;
	int diffy = source->lower_left.y - lower_left.y;
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

Bitmap::Bitmap(int w, int h, int bpp) : Clip(Point(0,0), w, h) 
{
	bit_per_pixel = bpp;
	for(int i=0; i<bpp; i++) bitmap[i] = new Clip(Point(0, 0), w, h);
}

int Bitmap::get_pixel(Point p)
{
	int b, ret;
	for(int i=0; i<bit_per_pixel; i++) {
		b = bitmap[i]->get_pixel(p);
		ret += b << i;
	}
	return ret;
}

void Bitmap::set_pixel(Point p, unsigned char v)
{
	bool t;
	for(int i=0; i<bit_per_pixel; i++) {
		t = (v >> i) & 1;
		bitmap[i]->set_pixel(p, t);
	}
}



