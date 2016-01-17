#pragma once
#include <cstddef>
#include "point.h"
enum bit_operation {SUBST, OR, AND, XOR, MINUS, NOT};

class Clip 
{
public:
	size_t **clip;
	Point lower_left;//lower left array의 비트맵에서의 uint 좌표
	int width, height;//width is * intSize

	Clip(Point lower_left, int width, int height);//직사각형 영역, 반드시 u_int형의 크기에 맞춤, basic
	Clip(Point center, int radius);//원을 포함하는 직사각형 영역
	Clip(Clip &cl1, Clip &cl2, bit_operation op);//두 개의 클립을 조인해서 만든다.
	Clip(Clip &cl, Point center, int radius);//다른 클립의 영역을 카피해서 만든다.
	~Clip();
	void clear();
	int set_lower_left(Point p);
	bool get_pixel(Point p);
	bool set_pixel(Point p, bool on_off);
	int operator = (Clip &clip);
	int paste_from(Clip* source, bit_operation op);

	Point bit_circle(Point center, int radius);//클립된 후의 중심좌표
	Point bit_arc(Point center, float angle_from, float angle_to);
	Point bit_arc_circle(Point center, int radius_from, int radius_to, float angle_from, float angle_to);
	float bit_arc_line(Point center, int radius, float angle_from, float angle_to);

protected:
	int flat_line(Point starting_point, int length);
	float bit_line(Point center, float theta);//중심점을 지나는 직선을 기준으로 좌우를 비트마스크 처리
	float correct_angle(float angle);

private:
	bool boundary_check(Point p);

};

class Bitmap : public Clip
{
public:
	Clip *bitmap[];
	int bit_per_pixel;
	
	Bitmap(int width, int height, int bpp);
	~Bitmap() {for(int i=0; i<bit_per_pixel; i++) delete bitmap[i];}
	void clear() {for(int i=0; i<bit_per_pixel; i++) bitmap[i]->clear();}
	int get_pixel(Point p);
	void set_pixel(Point p, unsigned char value);
	
protected:
	
private:
};

