#include<iostream>
#include"Unit.h"
#include"Util.h"
using namespace std;

int main()
{
	Unit u{"Infantry", Point{1,1}, 1};
	cout << u.get_fuel() << ' ' << u.get_currentHealth() << endl;
}
