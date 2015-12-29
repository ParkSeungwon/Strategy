#include "Terrain.h"
#include "Waypoint.h"
#include <cstdlib>
#include <ifstream>

unsigned int City::color_code = 0xff00ff;//분홍색
unsigned int Capital::color_code = 0xaa00ff;//보라색
unsigned int Airport::color_code = 0x5500ff;//연보라
unsigned int Harbor::color_code = 0x0000ff;//파란색
unsigned int Mountain::color_code = 0xff7000;//갈색
unsigned int Forest::color_code = 0x007f00;//진녹색
unsigned int Desert::color_code = 0xffff00;//노란색
unsigned int Swamp::color_code = 0x827f00;//어두운 노란색
unsigned int Sea::color_code = 0x00007f;//짙은 파란색
unsigned int River::color_code = 0x007f7f;
unsigned int Field::color_code = 0x00ff00;//녹색
unsigned int Road::color_code = 0x000000;//검은색
unsigned int Fort::color_code = 0xff0000;//빨간색
unsigned int Hill::color_code = 0x7f0000//짙은붉은색
int Terrain::movePenaltyVsInfantry = 0;
int Terrain::movePenaltyVsArmor = 0;
int Terrain::movePenaltyVsShip = 100;
int Terrain::evadeBonus = 20;
int City::movePenaltyVsInfantry = 0;
int City::movePenaltyVsArmor = 0;
int City::movePenaltyVsShip = 100;
int City::evadeBonus = 20;
int Capital::evadeBonus = 20;
int Airport::evadeBonus = 0;
int Harbor::movePenaltyVsShip = 0;
int Harbor::evadeBonus = 0;
int Mountain::movePenaltyVsInfantry = 30;
int Mountain::movePenaltyVsArmor = 100;
int Mountain::evadeBonus = 60;
int Forest::movePenaltyVsArmor = 50;
int Forest::movePenaltyVsInfantry = 20;
int Forest::evadeBonus = 30;
int Desert::movePenaltyVsInfantry = 60;
int Desert::movePenaltyVsArmor = 20;
int Desert::movePenaltyVsInfantry = 50;
int Desert::movePenaltyVsArmor = 70;
int Desert::evadeBonus = 10;
int Sea::movePenaltyVsInfantry = 100;
int Sea::movePenaltyVsArmor = 100;
int Sea::movePenaltyVsShip = 0;
int River::movePenaltyVsInfantry = 70;
int River::movePenaltyVsArmor = 70;
int River::movePenaltyVsShip = 30;
int Field::movePenaltyVsArmor = 10;
int Hill::movePenaltyVsInfantry = 30;
int Hill::movePenaltyVsArmor = 30;
int Hill::evadeBonus = 20;

Map::create_terrain_bitmap(char *filename)
{
	bit_per_pixel = 4;
}

Unit* City::produce_unit(char* unit_name, Point<int> p, float heading_toward) {
	//should access Map
	
