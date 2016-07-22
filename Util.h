#pragma once

namespace Glob {
	int find_big(int array[], int size);
	float correct_angle(float theta);
	int min(int x, int y);
	int max(int x, int y);
	const int OneTick = 1;
	enum class UnitType : int {Air, Armor, Infantry, Ship};
	
	enum class TerrainType : unsigned char {
		city, capital, airport, harbor, mountain, forest, 
		desert, sea, field, road, swamp, hill, river, fort
	};
	
	struct To_draw {
		int x, y, rmin, rmax;
		float angle_from, angle_to;
		double color[4];
	};

}

