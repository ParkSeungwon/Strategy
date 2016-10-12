#pragma once
#include "map.h"
class Darea;
struct TimeInterface {
	virtual void sync() = 0;
	virtual void time_pass() = 0;
};

class Time : public Map, public TimeInterface
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
