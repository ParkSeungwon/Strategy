#include "mysqldata.h"
using namespace std;

bool QueryData::create_table(SqlData& d)
{
	string q = "create table '" + d.table_name + "(";
	for(auto& a : d.structure) q += "'" + a.first + "' " + a.second + ",";
	q += d.extra + ")" + d.engine + ";";
	return myQuery(q);
}

bool QueryData::insert(SqlData& d)
{
	string q = "insert into '" + d.table_name + "' values ('";
	for(int i = 0; i < d.structure.size(); i++) {
		if(d.structure[i].second.find("int") == string::npos)//cannot find
			q += "'" + d.contents[i] + "', ";
		else q += d.contents[i] + ",";
	}
	q.back() = ')';
	q += ";";
	return myQuery(q);
}

vector<SqlData> QueryData::select(string table, string where)
{
	string q = "select * from " + table;
	if(where != "") q += " where " + where;
	q += ";";
	myQuery(q);

	SqlData d;
	vector<SqlData> v;
	sql::ResultSetMetaData* res_meta = res->getMetaData();
	int c = res_meta->getColumnCount();
	while(res->next()) {
		for(int i = 1; i <= c; i++) {
			d.structure[i].second = res_meta->getColumnType(i);
			d.structure[i].first = res_meta->getColumnName(i);
			if(d.structure[i].second.find("int") == string::npos)
				d.contents[i] = res->getString(i);
			else d.contents[i] = res->getInt(i);
		}
		v.push_back(d);
	}
	return v;
}

