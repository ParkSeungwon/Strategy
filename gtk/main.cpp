#include <gtkmm.h>
#include<iostream>
#include "win.h"
#include"Time.h"
using namespace std;

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
	for(auto& a : teams) for(auto& b : a) cout << b << ' ';
	cout << id << map;
    
//	for(auto& a : time.cities) {
		//cout << a.first << endl;
		//cout << a.first << ' ' <<  endl;
//	}
	return app->run(win);
}


