//client exe
#include "tcpip.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
	string s = "127.0.0.1";
	if(argc > 1) s = argv[1];
	Client cl(s);
	s == "";
	while(s != "end") {
		cin >> s;
		cl.send(s);
		cout << cl.recv() << endl;
	}
}

