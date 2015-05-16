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

Map::Map(char* filename) {
	ifstream fin(filename);
	fin >> width >> height;//한글도 잘 되고 나노도 있고
	bitSize = width * height / sizeof(unsigned int) + 1;
	intSize = 8 * sizeof(unsigned int);
	terrainTypeBitmask = (unsigned int) malloc(width * height * 4 / intSize +1);
	while(fin != null) fin >> terrainTypeBitmask++;
	
	fin.close();
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
