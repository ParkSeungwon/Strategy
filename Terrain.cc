//
///
//  Created 한 글입력이 이상합니다.d
//  Terrain.m
//  xCopyright (c) __MyCompanyName__. All rights reserved.
// //

#include "Terrain.h"
#include "Waypoint.h"
#include <cstdlib>
#include <ifstream>

Terrain::Terrain() {
	//terrainBitmask =  malloc(width * height * 3);
}

City::City()
{
	movePenaltyVsInfantry = 0;
	movePenaltyVsArmor = 0;
	movePenaltyVsShip = 100;
	evadeBonus = 20;
}

Capital::Capital()
{
	evadeBonus = 50;
}

Mountain::Mountain()
{
	movePenaltyVsInfantry = 50;
	movePenaltyVsArmor = 100;
	movePenaltyVsShip = 100;
	evadeBonus = 60;
}

Map::Map(char* filename) {
	ifstream fin(filename);//width, height, & bitwise info about terrains
	fin >> width >> height;//한글도 잘 되고 나노도 있고
	bitSize = width * height / sizeof(unsigned int) + 1;//
	intSize = 8 * sizeof(unsigned int);//bit of int=32
	terrainTypeBitmask = (unsigned int) malloc(width * height * 4 / intSize +1);//need 4 bit to show terrain type(less than 16)
	while(fin != null) fin >> terrainTypeBitmask++;
	
	fin.close();
}

Bitmap::Bitmap(int bpp)
{
	bit_per_pixel = bpp;
	bitmap = new unsigned int*[bit_per_pixel + 1];
	for(int i=0; i<bit_per_pixel; i++) {
		bitmap[i] = create_pane();
	}
}

Bitmap::~Bitmap()
{
	for(int i = 0; i < bit_per_pixel; i++) {
		delete [] bitmap[i];
	}
	delete [] bitmap;
}

int Bitmap::get_pixel_data(int x, int y)
{
	int share = (y * width + x) / intSize;
	int rest = (y * width + x) / intSize;
	unsigned int mask = 1 << (intSize - rest);
	int ret=0, b;
	for(int i=0; i<bit_per_pixel; i++) {
		b = bitmap[i][share] & mask;
		b = b >> (intSize - rest);
		ret += b << i;
	}
	return ret;
}

int Bitmap::flat_line(unsigned int* pane, IPoint s, int l)
{
	if(s.x + l >= width) l = width - s.x + 1;//바운더리 체크
	if(s.x < 0) s.x = 0;
	int ret = l;
	int share = xy_to_bit_share(s.x, s.y);
	int rest = xy_to_bit_rest(s.x, s.y);
	unsigned int mask;
	for(int i=0; l>0; i++) {
		if(intSize < rest + i) {
			share++;
			i = 0;
			rest = 0;
		}
		mask = 1 << (intSize - rest - i);
		pane[share] = pane[share] | mask;
		l--;
	}
	return ret;
}

unsigned int* Bitmap::bit_circle(IPoint c, int r)
{
	unsigned int* pane = create_pane();
	IPoint s;
	for(s.y = c.y - r; s.y <= c.y + r; s.y++) {
		if(s.y >= 0 && s.y < height) {
			s.x = c.x - sqrtf(r*r - (c.y-s.y)*(c.y-s.y));
			flat_line(pane, s, 2*(c.x-s.x) +1);
		}
	}
	return pane;
}

unsigned int* Map::make_arc_bitmap(CGPoint c, float sa, float ea)
{
	
}



terrainType MAP::getTerrainType(CGPoint position) {
	int share = (position.y * width + position.x) * 4 / intSize;
	int rest = (position.y * width + position.x) * 4 % intSize;
	return (*(bitmask+share+1) & (15 << (rest * (intSize-4) / 4 )) >>  (rest*(intSize-4)/4) );
}

unsigned int* Util::bitOperation(unsigned int *bitmaskA, unsigned int *bitmaskB, bitOperation option) {
	int i;
	//if(*bitmaskA != *bitmaskB) throw 1;
	unsigned int *bitmaskOR = (unsigned int*)malloc(bitSize);
	while(i++ < bitSize) {
		switch option {
			case OR:
				*bitmaskOR = *bitmaskA | *bitmaskB; break;
			case AND:
				*bitmaskOR = *bitmaskA & *bitmaskB; break;
			case XOR:
				*bitmaskOR = *bitmaskA ^ *bitmaskB; break;
		}
		bitmaskOR++; bitmaskA++; bitmaskB++;
	}
	return bitmaskOR;
}

unsigned int* Map::bitmask(CGPoint center, int radius) {	
	
	unsigned int *bitmask = (unsigned int*)malloc(bitSize);
	int x, y, bit=0;
	unsigned int i, *ptr = bitmask;
	
	while(y<height) {
		x = 0;
		while(x<width) {
			bit++;
			if((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) <= radius*radius) {
				i = i | (1 << (intSize-1-(bit%intSize)));
			}
			if(bit%intSize == intSize-1) {
				*ptr = i;
				ptr++;
				i =0 ;
			}
			x++;
		}
		y++;
	}
	return bitmask;
}

bool Map::inRange(unsigned int *bitmask, CGPoint position) {
	int share = (position.y * width + position.x) / intSize;//CGPoint int
	int rest = (position.y * width + position.x) % intSize;
	return *(bitmask+share+1) | 1 << (intSize-rest-1);
}

void deployUnit(Unit &unit) 
{
	int i;
	while (deployedUnit[unit.team][i++ ] != null);
	deployedUnit[unit.team][i] = &unit;
 }
