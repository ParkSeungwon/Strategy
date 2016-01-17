//dependent on libpng++-dev
class PNG_interface
{
public:
	static png_to_terrain_city_bitmap(char* filename, Bitmap& terrain, Bitmap& city);

private:
	bool find_color(png::basic_rgb_pixel<unsigned int> color;
};
