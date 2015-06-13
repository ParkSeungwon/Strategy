#include "png++/png.hpp"
 //...

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
	t.alloc(w, h, 4);
	c.alloc(w, h, 8);
	int i = 0;
	for (size_t y = 0; y < h; ++y) {
		for (size_t x = 0; x < w; ++x) {
			image[y][x].red;
			image[y][x].green;
			image[y][x].blue;
			if(!find_color(image[y][x])) {
				printf("i=%d, x=%d, y=%d, red=%x, green=%x, blue=%x\n",i, x, y, image[y][x].red, image[y][x].green, image[y][x].blue);
				colors[i++] = image[y][x];
			}
		}
	}
}
