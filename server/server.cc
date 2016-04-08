#include <iostream>
#include <string>
#include "server.h"
using namespace std;

vector<string> GameServer::logged_ids = {};//need to initialize static vector this way

string GameServer::operator()(string s) 
{
	logged_ids.push_back(s);
	string t;
	for(auto& a : logged_ids) t += a;
	//cout << t << endl;
	int i = 1;
	for(auto& a : logged_ids) cout << i++ << a << endl;
	return s;
}

int main()
{
	Server sv;
	GameServer gs;
	sv.start(gs);
}

