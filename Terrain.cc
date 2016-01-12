#include "Terrain.h"
using namespace std;

//#include <ifstream>
const float Terrain::move_penalty[4][14] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//air
	{1, 1, 1, 1, 0, 1.5, 1.2, 0, 1.2, 0.9, 1.7, 1.3, 0, 1.1},//armor
	{1, 1, 1, 1, 1.7, 1.2, 1.3, 0, 1, 1, 1.5, 1.3, 0, 1.1},//infantry
	{0, 0, 0, 1.3, 0, 0, 0, 1, 0, 0, 0, 0, 1.3, 0}//sea
};

const unsigned int Terrain::color_code[14] = { 
	0xff00ff,//분홍색 
	0xaa00ff,//보라색
	0x5500ff,//연보라
	0xff,//파랑
	0xff7000, //갈색
	0x7f00,//진녹색
	0xffff00,//노란색
	0x827f00,//어두운 노란색
	0x7f, //짙은 파란색
	0x7f7f,
	0xff00,//녹색
	0x0, //검은색
	0xff0000,//빨강
	0x7f0000//짙은 붉은색
};

const float Terrain::evade_bonus[4][14] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//air
	{1.2, 1.4, 1.1, 1, 1.5, 1.2, 0.9, 0.9, 1, 1, 0.7, 1.2, 1, 1.5},
	{1.3, 1.5, 1.1, 1.1, 2, 1.3, 1, 1, 1, 1, 0.8, 1.2, 1, 1.7},
	{1, 1, 1, 1.1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

Glob::TerrainType Terrain::get_terraintype_by_color(unsigned int code)
{
	int i = 0;
	switch(code) {
		case 0xff00ff : i++;//분홍색
		case 0xaa00ff : i++; //보라색
		case 0x5500ff : i++;//연보라
		case 0xff : i++; //파랑
		case 0xff7000 : i++; //갈색
		case 0x7f00 : i++; //진녹색
		case 0xffff00 : i++; //노란색
		case 0x827f00 : i++;//어두운 노란색
		case 0x7f : i++;//짙은 파란색
		case 0x7f7f : i++; 
		case 0xff00 : i++;//녹색
		case 0x0 : i++; //검은색
		case 0xff0000: i++; //빨강
		case 0x7f0000: i++;//짙은 붉은색
		default : ; 
	}
	return (Glob::TerrainType)(14-i);
}
	
float Terrain::get_move_penalty(Glob::TerrainType tt, Glob::UnitType ut) 
{
	return move_penalty[(int)ut][(int)tt];
}

float Terrain::get_evade_bonus(Glob::TerrainType tt, Glob::UnitType ut)
{
	return evade_bonus[(int)ut][(int)tt];
}
