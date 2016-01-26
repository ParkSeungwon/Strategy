#pragma once

class Terrain_data 
{
public:
	virtual ~Terrain_data();
	Terrain_data();
	Terrain_data(int w, int h);
	Terrain_data(Terrain_data&& tr);
	Terrain_data& operator=(Terrain_data&& tr);
	int width, height;
	size_t **tmap;
};

