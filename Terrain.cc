#include "Terrain.h"
#include <iostream>
#include "Util.h"
using namespace std;
using namespace Glob;

//#include <ifstream>
const float Terrain::move_penalty[4][14] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//air
	{1, 1, 1, 1, 0, 1.5, 1.2, 0, 1.2, 0.9, 1.7, 1.3, 0, 1.1},//armor
	{1, 1, 1, 1, 1.7, 1.2, 1.3, 0, 1, 1, 1.5, 1.3, 0, 1.1},//infantry
	{0, 0, 0, 1.3, 0, 0, 0, 1, 0, 0, 0, 0, 1.3, 0}//sea
};

const unsigned char Terrain::color_code[14][3] = { 
	{0xff, 0x00, 0xff},///<분홍색city 
	{0xaa, 0x00, 0xff},///<보라색capital
	{0x55, 0x00, 0xff},///<연보라airport
	{0x00, 0x00, 0xff},///<파랑harbor
	{0xff, 0x70, 0x00}, //갈색mountain
	{0x00, 0x7f, 0x00},//진녹색forest
	{0xff, 0xff, 0x00},//노란색desert
	{0x00, 0x00, 0x7f}, //짙은 파란색sea
	{0x00, 0xff, 0x00},//녹색field
	{0x00, 0x7f, 0x7f},//teal road
	{0x82, 0x7f, 0x00},//어두운 노란색swamp
	{0xff, 0x00, 0x00},//빨강fort
	{0x00, 0x00, 0x00},//검은색 river
	{0x7f, 0x00, 0x00}//짙은 붉은색fort
};

const string Terrain::name[14] = {
	"city", "capital", "airport", "harbor", "mountain", "forest", "desert", 
	"sea", "field", "road", "swamp", "hill", "river", "fort"
};



const float Terrain::evade_bonus[4][14] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//air
	{1.2, 1.4, 1.1, 1, 1.5, 1.2, 0.9, 0.9, 1, 1, 0.7, 1.2, 1, 1.5},
	{1.3, 1.5, 1.1, 1.1, 2, 1.3, 1, 1, 1, 1, 0.8, 1.2, 1, 1.7},
	{1, 1, 1, 1.1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

TerrainType Terrain::get_terraintype_by_color(unsigned char r, unsigned char g, unsigned char b)
{
	for(int i=0; i<14; i++) {
		if(color_code[i][0] == r && color_code[i][1] == g && color_code[i][2] == b) 
			return static_cast<TerrainType>(i);
	}
	return TerrainType::river;
}

	
float Terrain::get_move_penalty(Glob::TerrainType tt, Glob::UnitType ut) 
{
	return move_penalty[(int)ut][(int)tt];
}

float Terrain::get_evade_bonus(Glob::TerrainType tt, Glob::UnitType ut)
{
	return evade_bonus[(int)ut][(int)tt];
}
