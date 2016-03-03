#pragma once
#include <string>
#include <vector>
#include "mysqlquery.h"

struct SqlData
{
	static std::string table_name;
	static std::vector<std::pair<std::string, std::string>> structure;
	static std::string extra;
	static std::string engine;
	std::vector<std::string> contents;
};

class QueryData : public Mysqlquery
{
public:
	bool create_table(SqlData& data);
	bool insert(SqlData& data);
	std::vector<SqlData> select(std::string table, std::string where = "");
};

