#include<iostream>
#include"Unit.h"
#include"Util.h"
#include"Weapon.h"
#include"mysqldata.h"
#include"gtk/interface.h"
#include"mapinterface.h"
#include<gtkmm.h>
using namespace std;

extern FieldInterface* fInterface;
vector<array<int, 3>> setup(int capital_count);
extern const char *Type[], *Nations[];
extern map<string, int> Teams;

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "");
	auto t = setup(3);
	for(int i=0; i<10; i++) cout << Nations[i];
	for(auto& a : t) {
		for(int i=0; i<3; i++) cout << a[i] << ' ';
		Teams[Nations[a[1]]] = a[1];
		//cout << a[0] << Teams[Nations[a[1]]] << endl;
	}
	return app->run();

}
