#include <cstddef>
#include "terrain_data.h"

Terrain_data::Terrain_data(int w, int h)
{
	width = w;
	height = h;
	tmap = new char[w * h * 4];
}

Terrain_data::Terrain_data(Terrain_data&& tr)
{
	width = tr.width;
	height = tr.height;
	tmap = tr.tmap;
	tr.tmap = nullptr;
}

char* Terrain_data::pixel(unsigned x, unsigned y)
{ 
	return tmap + 4 * (y * width + x);
}

Terrain_data::Terrain_data()
{
	tmap = nullptr;
}

Terrain_data::~Terrain_data()
{
	del_tmap();
}

Terrain_data& Terrain_data::operator=(Terrain_data&& tr)
{
	if(this == &tr) return *this;
	width = tr.width;
	height = tr.height;

	del_tmap();
	tmap = tr.tmap;
	tr.tmap = nullptr;
	return *this;
}

bool Terrain_data::del_tmap()
{
	if(tmap != nullptr) {
		delete [] tmap;
		return true;
	} else return false;
}
