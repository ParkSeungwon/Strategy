#include <gtkmm.h>
#include<iostream>
#include "win.h"
#include"Time.h"
using namespace std;

extern const char *Type[], *Nations[];
extern map<string, int> Teams;
string login(string prog_id, string prog_pass);//in conndata.cc, find with grep
string choose_map();
vector<array<int, 3>> setup(int capital_count);

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "");

	string id = login("strategy", "strategy");
	if(id == "exit") return 0;
	
	string map = choose_map();
	if(map == "exit") return 0;
	
	Time time;//model
	Win win;//view
	
	int capital_count = time.init_map(win.open_map_file(map));
	auto teams = setup(capital_count);
	if(teams.empty()) return 0;
	for(auto& a : teams) {
		cout << Type[a[0]] << " : " << Nations[a[1]] << ", team" << a[2] << endl;
		Teams[Nations[a[1]]] = a[2];
	}
	cout << id << map;
   	time.locate_nations(); 
	return app->run(win);
}


