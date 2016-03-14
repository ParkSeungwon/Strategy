#pragma once
#include <string>
#include <vector>
#include "mysqlquery.h"

struct SqlData
{
	std::string table_name;
	std::vector<std::pair<std::string, std::string>> structure;
	std::string extra;
	std::string engine;
	std::vector<std::string> contents;
};

class QueryData : public Mysqlquery
{
public:
	bool create_table(const SqlData& data);
	bool insert(const SqlData& data);
	SqlData select(std::string table, std::string where = "");
	static std::string now();//system clock->mysql datetime string
};

