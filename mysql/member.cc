#include <iostream>
#include "mysqldata.h"
using namespace std;

int main()
{
	SqlData member;
	member.structure =  {
		{"email", "char(30) NOT NULL"},
		{"password", "char(45) DEFAULT NULL"},
		{"level", "tinyint(4) DEFAULT NULL"},
		{"name", "varchar(45) DEFAULT NULL"},
		{"tel", "varchar(20) DEFAULT NULL"},
		{"date", "datetime NOT NULL"}
	};
	member.table_name = "Users";
	member.extra = "primary key (email, date)";
	member.engine = "ENGINE=MyISAM DEFAULT CHARSET=utf8";
	
	QueryData qd;
	qd.connect("localhost", "strategy", "strategy", "strategy");//host, id, pass, database
	qd.create_table(member);
	member.contents = { "zezeon@msn.com", "cockcodk", "1", "Park Seungwon",
		"031-255-6698", qd.now()};
	qd.insert(member);
	SqlData s = qd.select("Users", "email = 'zezeon@msn.com' and password = 'cockcodk'");
	for(auto& a : s.contents) cout << a << endl;
}

