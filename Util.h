#pragma once

class Util {
public:
	static int min(int a, int b) {return a<b ? a:b;}
	static int max(int a, int b) {return a>b ? a:b;}
	static int find_big(int array[], int size);
	static float correct_angle(float theta);
};

