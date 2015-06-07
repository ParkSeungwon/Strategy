
class Map : public Terrain
{
private:
	unsigned int width, height;
	const static int maxTeam = 8;
	const static int maxUnit = 100;
	
protected:
	static unsigned int* bitmask(CGPoint center, int radius);
	static unsigned int* bitOperation(unsigned int *bitmaskA, unsigned int *bitmaskB, bitOption option);
	static bool inRange(unsigned int *bitmask, CGPoint position);
	Bitmap terrain_bitmap, unit_bitmap, recon_bitmap, wepon_range_bitmap, city_bitmap;
	
public:
	Terrain whole_map[width][height];
	Unit* deployedUnits[maxTeam][maxUnit];
	terrainType getTerrainType(CGPoint _position);
	Map(char* filename);
	void deployUnit(Unit &unit);
};

