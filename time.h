#define Turn = 100 Tick
#define Tick = 3 sec
#include "map.h"

class Time : public Map
{
	private:
		const static int oneTick = 4;
	protected:
	
	public:
		double clock;
		int oneTickPass() ;
		void time_pass(int time);
};
