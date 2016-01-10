#include <vector>
using namespace std;
class A {
	public:
	//	void operator=(A ta) {a = ta.a;}
		int a;
};
class B : public A {
	public:
		int b;
};

int main(int argc, char *argv[])
{
	A ca;
	vector<A> v;
	v.push_back(ca);
	auto it = v.begin();
	v.erase(it);
	A cc = A(ca);

/*	A ca;
	B cb;
	ca.a = 5;
//	cb.a = 3;
	cb.b = 4;
	cb = (B)ca;

	co << ca.a << cb.a << cb.b << endl;
	*/
}
