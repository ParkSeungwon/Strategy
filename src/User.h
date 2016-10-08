#pragma once

class User
{
public:
	int type, team, id;
	std::string nation;
	int money;
	deployUnit(Map& map, Unit unit);
};
