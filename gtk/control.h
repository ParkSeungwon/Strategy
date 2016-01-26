//#include "../time.h"
//#include "darea.h"
class Time;
class Darea;
class Win;

struct User
{
	int ally;
	int team;
};

class Control 
{
public:
	Control(Win& w, User& u);
	void sync();
	Win* win;
	Darea* area;
	Time* time;
	User user;
	double color[8][4];
};
