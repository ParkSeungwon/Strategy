#pragma once

class User
{
public:
	int type;//human, user, cpu
	std::string nation;
	int money;
	deployUnit(Map& map, Unit unit);
};

