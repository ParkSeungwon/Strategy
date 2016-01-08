#include "cout.h"
using namespace std;

class A {
	public:
		void operator=(A ta) {a = ta.a;}
		int a;
};
class B : public A {
	public:
		int b;
};

int main(int argc, char *argv[])
{
	A ca;
	B cb;
	ca.a = 5;
//	cb.a = 3;
	cb.b = 4;
	cb = (B)ca;

	co << ca.a << cb.a << cb.b << endl;
}
