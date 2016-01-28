#include <cstddef>
#include "terrain_data.h"

Terrain_data::Terrain_data(int w, int h)
{
	width = w;
	height = h;
	tmap = new size_t*[w];
	for(int i=0; i<w; i++) tmap[i] = new size_t[h];
}

Terrain_data::Terrain_data(Terrain_data&& tr)
{
	width = tr.width;
	height = tr.height;
	tmap = tr.tmap;
	tr.tmap = nullptr;
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
		for(int i=0; i<width; i++) delete [] tmap[i];
		delete [] tmap;
		return true;
	} else return false;
}
