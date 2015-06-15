class Map : public Terrain
{
private:
	unsigned int width, height;
	const static int maxTeam = 8;
	const static int maxUnit = 100;
	
protected:
	static bool inRange(unsigned int *bitmask, CGPoint position);
	Bitmap terrain_bitmap, recon_bitmap, weapon_range_bitmap, city_bitmap;
	
public:
	Unit* deployedUnits[maxTeam][maxUnit];
	terrainType getTerrainType(CGPoint _position);
	Map(char* PNG_filename);//Read png file to init bitmaps
	void deployUnit(Unit &unit);
};

