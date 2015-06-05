struct IPoint {
	int x,y;
};

struct Clip {
	unsigned int **clip;
	int x, y;//lower left array의 비트맵에서의 uint 좌표
	int array_width, array_height;//width is * intSize
};

class Bitmap
{
public:
	int width, height;
	unsigned int ***bitmap;
	int bit_per_pixel;
	int bitSize, intSize;
	
	Bitmap(int bit_per_pixel);
	~Bitmap();
	
protected:
	int flat_line(unsigned int* pane, IPoint start_point, int longevity);
	int get_pixel_data(Bitmap* bitmap, int x, int y);
	
	
private:
	unsigned int* create_pane(){return new unsigned int[width * height / intSize + 1];}
	Clip* create_clip(IPoint center, int radius, int layer = 0);//원을 둘러싼 정사각형을 클립한다.
	void paste_clip(Clip* cl, int layer = 0);
	IPoint* 
	int xy_to_bit_share(int x, int y) {return (y * width + x) / intSize;}
	int xy_to_bit_share(IPoint p) {return (p.y * width + p.x) / intSize;}
	int xy_to_bit_rest(int x, int y) {return (y * width + x) % intSize;}
	int xy_to_bit_rest(IPoint p) {return (p.y * width + x) % intSize;}
};
