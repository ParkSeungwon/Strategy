#include "png++/png.hpp"
#include "Terrain.h"

png::basic_rgb_pixel<unsigned char> colors[10000];

bool PNG_interface::find_color(png::basic_rgb_pixel<unsigned char> c) 
{
	for(int i=0; i<10000; i++) {
		if(c.red == colors[i].red && c.green == colors[i].green && c.blue == colors[i].blue) {
			return true;
		}
	}
	return false;
}

PNG_interface::png_to_terrain_city_bitmap(char* filename, Bitmap& t, Bitmap& c)
{
	png::image< png::rgb_pixel > image(filename);
	int h = image.get_height();
	int w = image.get_width();
	&t = new Bitmap(w, h, 4);
	&c = new Bitmap(w, h, 8);
	int i = 0;
	Point<int> p;

	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			p.x = x; p.y = y;
			if(image[y][x].blue == 0xff) {//생산가능한 지형은 모두 블루값이 0xff임.
				c.set_pixel(p, image[y][x].green);//도시의 고유번호를 부여함
				switch(image[y][x]) {
					case City::color_code : 	t.set_pixel(p, city); 	break;
					case Capital::color_code : 	t.set_pixel(p, capital);break;
					case Harbor::color_code : 	t.set_pixel(p, harbor); break;
					case Airport::color_code : 	t.set_pixel(p, airport);
				}
			} 
			else {
				switch(image[y][x]) {
					case Field::color_code : 	t.set_pixel(p, field); 		break;
					case Mountain::color_code : t.set_pixel(p, mountain); 	break;
					case Sea::color_code : 		t.set_pixel(p, sea); 		break;
					case Road::color_code : 	t.set_pixel(p, road); 		break;
					case Hill::color_code : 	t.set_pixel(p, hill); 		break;
					case Swamp::color_code : 	t.set_pixel(p, swamp); 		break;
					case Fort::color_code : 	t.set_pixel(p, fort); 		break;
					case Forest::color_code : 	t.set_pixel(p, forest); 	break;
					default : 					t.set_pixel(p, river);
				}
			}
		}
	}
}
