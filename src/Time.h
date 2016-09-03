#pragma once
#include "map.h"
class Darea;

class Time : public Map
{
public:
  	Time(Darea& d);
	double clock;
	int oneTickPass() ;
	void time_pass();

protected:
  	Darea& battlefield;
private:
  	void sync();
};
