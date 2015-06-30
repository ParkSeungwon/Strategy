class Unit;

class Weapon 
{
public:
	Clip* fire_range_clip;
	int adjust_range_clip(WhereAbout& wh);
	int operator >> (Unit &enenmy);		//공격 함수
	int operator >> (Unit *enemy[]);//현재 설정된 프레퍼런스에 따라 배열 중 하나의 적을 선택하여 공격
	int operator + (Unit& enemy);//target return expected value regards to preference 

	Weapon(string filename, string weaponName);

protected:
	static int fireRate, firePower, maxRounds;
	static int hitRatioVSAir, hitRatioVsArmor, hitRatioVsInfantry, hitRatioVsShip;
	static int shootingRangeMin, shootingRangeMax;
	static int shootingAngleFrom, shootingAngleTo;
	int lapsedTimeAfterFire;
	int currentRounds;
	enum Preference {LOW_HEALTH, HIGH_DAMAGE, HIGH_RATIO, EXPENSIVE, CHEAP} preference;
	int hitRate(Unit& enemy);
	int* dice_record;//to record dice data for replay
	int* current_dice;
};
