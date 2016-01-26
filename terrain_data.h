#pragma once
//move syntax realize
class Terrain_data 
{
public:
	virtual ~Terrain_data();
	Terrain_data();
	Terrain_data(int w, int h);
	Terrain_data(Terrain_data&& tr);
	Terrain_data& operator=(Terrain_data&& tr);
	int width, height;
	size_t **tmap;//access by tmap[x][y]

private:
	bool del_tmap();
};

