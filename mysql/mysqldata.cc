#include <chrono>
#include <ctime>
#include <unordered_map>
#include "mysqldata.h"
using namespace std;

bool QueryData::create_table(const SqlData& d)
{
	string q = "create table " + d.table_name + " (";
	for(auto& a : d.structure) q += " " + a.first + " " + a.second + ", ";
	q += d.extra + " ) " + d.engine + ";";
	return myQuery(q);
}

bool QueryData::insert(const SqlData& d)
{
	string q = "insert into " + d.table_name + " values (";
	for(int i = 0; i < d.structure.size(); i++) {
		if(d.structure[i].second.find("int(") != string::npos)//can find
			q += d.contents[i] + ",";
		else q += "'" + d.contents[i] + "',";
	}
	q.back() = ')';
	q += ";";
	return myQuery(q);
}

SqlData QueryData::select(string table, string where)
{
	string q = "select * from " + table;
	if(where != "") q += " where " + where;
	q += ";";
	myQuery(q);

	SqlData d;
	d.table_name = table;
	sql::ResultSetMetaData* res_meta = res->getMetaData();
	int c = res_meta->getColumnCount();
	for(int i = 0; i < c; i++) {
		d.structure.push_back({res_meta->getColumnName(i+1), 
				res_meta->getColumnTypeName(i+1)});
	}
	while(res->next()) {
		for(int i = 0; i < c; i++) {
			d.contents.push_back(res->getString(i+1));
		}
	}
	return d;
}

string QueryData::now()
{
	auto now = chrono::system_clock::now();
	auto tp = chrono::system_clock::to_time_t(now);
	string t = ctime(&tp);
	unordered_map<string, string> months {
		{"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"}, 
		{"May", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"}, 
		{"Sep", "09"}, {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}
	};

	string s = t.substr(20, 4) + "-" + months[t.substr(4, 3)] + "-";
	if(t[8] == ' ') s += '0';
	else s += t[8];
	s += t.substr(9, 10);
	return s;
}


