#include "Util.h"
int randomDice(int eyes) {
	srand(time());
	return rand()%eyes;
}

int randomDice() {
	return randomDice(100);
}

float Util::correct_angle(float theta)
{
	while(theta > 2 * M_PI) theta -= 2 * M_PI;
	while(theta < 0) theta += 2 * M_PI;
	return theta;
}

int Util::find_big(int ar[], int s)
{
	int index = 0;
	for(int i=0; i<s; i++) {
		if(ar[i] > ar[index]) index = i;
	}
	return index;
}
