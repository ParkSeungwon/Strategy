#pragma once
#include "map.h"

class Time : public Map
{
	private:
	protected:
	
	public:
		Time(int w, int h, size_t** p, int a) : Map(w, h, p, a) {}
		double clock;
		int oneTickPass() ;
		void time_pass();
};
