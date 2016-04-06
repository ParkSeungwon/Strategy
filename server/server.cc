#include <iostream>
#include <string>
#include "server.h"
using namespace std;

string GameServer::operator()(string s) {
	
	logged_ids.push_back(s);
	string t;
	for(auto& a : logged_ids) t += a;
	cout << t << endl;
	return t;
}

int main()
{
	Server sv;
	sv.start(GameServer());
}

