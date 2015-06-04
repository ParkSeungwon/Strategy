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

unsigned int* Map::make_bitmap(int bit_per_pixel)
{
	unsigned int alloc[] = new unsigned int[width*hei/intSize + 1][bit_per_pixel];
	unsigned int* alloc = new unsigned int[w * h * bit_per_pixel / intSize + 5];
	alloc[0] = w;
	alloc[1] = h;
	alloc[2] = bit_per_pixel;
}

unsigned int Map::get_pixel_data(unsigned int *bitmap, int x, int y)
{
	int b = bitmap[2];
	int share = (y * bitmap[0] + x) * b / intSize;
	int rest = (y * bitmap[0] + x) * b % intSize;
	
	unsigned long l = (unsigned long)bitmap[share+3] << intSize 
	l += bitmap[share+4};//두개를 연결시킴
	unsigned long mask = 2 << b - 1;
	mask = mask << (2*intSize - b - rest);
	l = l & mask;
	l = l >> (2*intSize - b - rest);
	return l;
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
