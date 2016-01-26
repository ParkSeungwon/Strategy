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
	if(tmap != nullptr) {
		for(int i=0; i<width; i++) delete [] tmap[i];
		delete [] tmap;
	}
}

Terrain_data& Terrain_data::operator=(Terrain_data&& tr)
{
	width = tr.width;
	height = tr.height;

	if(tmap != nullptr) {
		for(int i=0; i<width; i++) delete [] tmap[i];
		delete [] tmap;
	}
	tmap = tr.tmap;
	tr.tmap = nullptr;
	return *this;
}


