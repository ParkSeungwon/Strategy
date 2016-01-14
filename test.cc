#include <iostream>
using namespace std;
class A {
	public:
		A(int j) : i(j) {}
	//	A& operator=(A& a) {return a;}
		virtual void change() { i = 88;}
		~A() {std::cout << i;}
		int i;
};

class B: public A {
	public:
		void change() { i = 34;}
	B(int i):A(i){}
};

int main () {
	A a(33);
	B b(22);
	b.A::change();
	cout << "a.i " << a.i << endl;
	cout << "b.i " << b.i << endl;
	
}
