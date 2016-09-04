#pragma once
#include "map.h"
class Darea;

class Time : public Map
{
public:
  	Time();
	double clock;
	int oneTickPass() ;
	void time_pass();

protected:
private:
  	void sync();
};
