#pragma once
#include"Util.h"

class Interface
{
public:
	virtual void set_user(std::string user) = 0;
};

struct FieldInterface
{
	virtual void paste_pix(int x, int y, std::string name, float heading = 0) = 0;
	virtual void insert_to_draw(const Glob::To_draw& td) = 0;
};
