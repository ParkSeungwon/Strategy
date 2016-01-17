#include <iostream>
#include <vector>
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

void fu(int& i, vector<int>& v) {v.push_back(i);}
int f() {return 4;}
int main () {
/*	A a(33);
	B b(22);
	b.A::change();
	cout << "a.i " << a.i << endl;
	cout << "b.i " << b.i << endl;
*/	
		vector<int> v;
		v.push_back(31);
		int j = 54;
		fu(j, v);
		j = 43;
//		for(auto& i : v) cout << i;
}
