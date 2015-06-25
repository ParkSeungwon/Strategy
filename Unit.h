class Unit : public Waypoint<T>
{
public:
	int team;
	static unsigned int unitPrice;
	static unsigned int maxHealth;
	int currentHealth;
	int minimumTurnRadius;
	int minimumSpeed;
	int maximumSpeed;
	Weapon* weaponSlot[10];
	Clip* recon_clip;
	unsigned int intelligenceRadius;

	Clip* movable_area(int time);//generate clip of movable area within time
	
	BOOL canEquip:(Weapon *)weapon;
	
	Unit(string _unitName, CGPoint _position, float _headingToward);

	Unit(terrain_bitmap& tb) {t_bitmap = tb;};
	string unitName;
	const static int maxWayPoint = 10;
	terrain_bitmap* ptr_terrain_bitmap;
	recon_bitmap* ptr_recon_bitmap;
	weapon_range_bitmap* ptr_weapon_range_bitmap;

	Clip* movable_area(int time);
	bool operator + (Unit& enemy, Weapon *w);//target 공격가능한지  
	int operator + (Unit enemy[], Weapon *w);//프레퍼런스에 따라 배열 중의 유닛을 선택한다.
	int operator >> (Unit &enemy, Weapon *w);
	int operator >> (Unit enemy[], Weapon *w);//여럿중의 하나를 선택하여 공격
	int operator + (Weapon& weapon);//equip weapon
	int operator - (Weapon& weapon);//unload weapon
protected:
	static int evadeRatio;
	int fuelCapacity;
	int fuel;
	unsigned int experience;


private:
	int movable_line(IPoint turn_center, int time, Clip *cl);
};

unsigned int Unit::price;

class TerrainUnit : public Unit//지형효과를 받는 유닛들의 모클래스
{
public:
	int insert_waypoint(FPoint turn_center, int spd, int dur);//return inserted nth waypoint 지형효과를 고려함
	static unsigned int terrainPenaltyPercent;
};

class AirUnit : public Unit 
{
	terrainPenaltyPercent = 0;
	AirUnit(string _unitName, CGPoint _currentPosition) : Unit(_unitName, _currentPosition);
	int land_on(Airport& airport);
};

class ArmorUnit : public TerrainUnit 
{
	WhereAbout<int> time_pass(int time);	
};

class InfantryUnit : public TerrainUnit 
{
	WhereAbout<int> time_pass(int time);
	int occupy(City& city);
};

class ShipUnit : public TerrainUnit 
{
	WhereAbout<int> time_pass(int time);

};

