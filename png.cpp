#include <png++/png.hpp>
 //...

png::basic_rgb_pixel<unsigned char> colors[10000];

bool find_color(png::basic_rgb_pixel<unsigned char> c) 
{
	for(int i=0; i<10000; i++) {
		if(c.red == colors[i].red && c.green == colors[i].green && c.blue == colors[i].blue) {
			return true;
		}
	}
	return false;
}
int main() 
{
 	png::image< png::rgb_pixel > image("1.png");
	int i = 0;
	for (size_t y = 0; y < image.get_height(); ++y)
	{
    	for (size_t x = 0; x < image.get_width(); ++x)
    	{
			if(!find_color(image[y][x])) {
				printf("i=%d, x=%d, y=%d, red=%x, green=%x, blue=%x\n",i, x, y, image[y][x].red, image[y][x].green, image[y][x].blue);
				colors[i++] = image[y][x];
        	// non-checking equivalent of image.set_pixel(x, y, ...);
			}
     	}
 	}
}

