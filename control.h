//#include "../time.h"
//#include "darea.h"
class Time;
class Darea;

class Control 
{
public:
	Control(Darea& ar, Time& t);
	void sync();
	Darea* darea;
	Time* time;
};
