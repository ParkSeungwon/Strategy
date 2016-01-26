//#include "../time.h"
//#include "darea.h"
class Time, Darea;

class Control 
{
public:
	Control(Darea& ar, Time& t);
	sync();
	Darea* darea;
	Time* time;
};
