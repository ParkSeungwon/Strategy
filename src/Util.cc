#include "Util.h"
#include <math.h>

float Glob::correct_angle(float theta)
{
	while(theta > 2 * M_PI) theta -= 2 * M_PI;
	while(theta < 0) theta += 2 * M_PI;
	return theta;
}

int Glob::find_big(int ar[], int s)
{
	int index = 0;
	for(int i=0; i<s; i++) {
		if(ar[i] > ar[index]) index = i;
	}
	return index;
}

int Glob::min(int x, int y)
{
	return x<y ? x : y;
}

int Glob::max(int x, int y)
{
	return x>y ? x : y;
}
