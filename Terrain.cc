#include "Terrain.h"
#include "Waypoint.h"
#include <cstdlib>
//#include <ifstream>
Terrain::Terrain() {
	movePenaltyVsInfantry = 0;
	movePenaltyVsArmor = 0;
	movePenaltyVsShip = 100;
	evadeBonus = 20;
}
City::City() {
	color_code = 0xff00ff;//분홍색
	movePenaltyVsInfantry = 0;
	movePenaltyVsArmor = 0;
	movePenaltyVsShip = 100;
	evadeBonus = 20;
}
Capital::Capital() {
	color_code = 0xaa00ff;//보라색
	evadeBonus = 20;
}
Airport::Airport() {
	color_code = 0x5500ff;//연보라
	evadeBonus = 0;
}
Harbor::Harbor() {
	color_code = 0x0000ff;//파란색
	movePenaltyVsShip = 0;
	evadeBonus = 0;
}
Mountain::Mountain() {
	color_code = 0xff7000;//갈색
	movePenaltyVsInfantry = 30;
	movePenaltyVsArmor = 100;
	evadeBonus = 60;
}
Forest::Forest() {
	color_code = 0x007f00;//진녹색
	movePenaltyVsArmor = 50;
	movePenaltyVsInfantry = 20;
	evadeBonus = 30;
}
Desert::Desert() {
	color_code = 0xffff00;//노란색
	movePenaltyVsInfantry = 60;
	movePenaltyVsArmor = 20;
	movePenaltyVsInfantry = 50;
	movePenaltyVsArmor = 70;
	evadeBonus = 10;
}
Swamp::Swamp() {
	color_code = 0x827f00;//어두운 노란색
}
Sea::Sea() {
	color_code = 0x00007f;//짙은 파란색
	movePenaltyVsInfantry = 100;
	movePenaltyVsArmor = 100;
	movePenaltyVsShip = 0;
}
River::River() {
	color_code = 0x007f7f;
	movePenaltyVsInfantry = 70;
	movePenaltyVsArmor = 70;
	movePenaltyVsShip = 30;
}
Field::Field() {
	color_code = 0x00ff00;//녹색
	movePenaltyVsArmor = 10;
}
Road::Road() {
	color_code = 0x000000;//검은색
}
Fort::Fort() {
	color_code = 0xff0000;//빨간색 
	evadeBonus = 70;
}
Hill::Hill() {
	color_code = 0x7f0000;//짙은붉은색
	movePenaltyVsInfantry = 30;
	movePenaltyVsArmor = 30;
	evadeBonus = 20;
}

Unit* City::produce_unit(char* unit_name, Point<int> p, float heading_toward) {
	//should access Map
}	
Unit* Land::produce_unit()
