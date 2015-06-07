
Map::Map(char* filename) {
	ifstream fin(filename);//width, height, & bitwise info about terrains
	fin >> width >> height;//한글도 잘 되고 나노도 있고
	terrain_bitmap.alloc(width, height, 4);
	terrainTypeBitmask = (unsigned int) malloc(width * height * 4 / intSize +1);//need 4 bit to show terrain type(less than 16)
	while(fin != null) fin >> terrainTypeBitmask++;
	
	fin.close();
}

bool Map::inRange(unsigned int *bitmask, CGPoint position) {
	int share = (position.y * width + position.x) / intSize;//CGPoint int
	int rest = (position.y * width + position.x) % intSize;
	return *(bitmask+share+1) | 1 << (intSize-rest-1);
}

void deployUnit(Unit &unit) 
{
	int i;
	while (deployedUnit[unit.team][i++ ] != null);
	deployedUnit[unit.team][i] = &unit;
 }
