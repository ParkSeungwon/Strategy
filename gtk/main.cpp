#include <gtkmm.h>
#include<iostream>
#include "win.h"
#include"Time.h"
using namespace std;

string login(string prog_id, string prog_pass);
string choose_map();

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "");
	string id = login("strategy", "strategy");
	if(id == "exit") return 0;
	string map = choose_map();
	if(map == "exit") return 0;
	cout << id;
	Time time;
	Win win;
	time.init_map(win.open_map_file(map));
    return app->run(win);
}


