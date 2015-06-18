struct IPoint {
	int x,y;
};

class Clip 
{
public:
	Clip* circle_clip(IPoint center, int radius);//원을 포함하는 직사각형 영역
	Clip(IPoint lower_left, int width, int height);//직사각형 영역, 반드시 u_int형의 크기에 맞춤
	Clip() {}
	~Clip();
	Clip* join_clip(Clip *cl1, Clip* cl2, bitOperation op);
	int flat_line(IPoint starting_point, int length);
	IPoint bit_circle(Clip *cl, IPoint center, int radius);//클립된 후의 중심좌표

	unsigned int **clip;
	IPoint lower_left;//lower left array의 비트맵에서의 uint 좌표
	int width, height;//width is * intSize
};

class Bitmap : public Clip
{
public:
//	int width, height;// in pixel
	unsigned int ***bitmap;
	int bit_per_pixel;
	int bitSize, intSize;
	
	~Bitmap();
	int alloc(int width, int height, int bit_per_pixel);
	IPoint bit_arc_circle(Clip *cl, IPoint center, int radius_from, int radius_to, float angle_from, float angle_to);
	clear();
	
protected:
	int get_pixel_data(int x, int y);
	bool get_pixel_of_layer(int x, int y, int layer);
	int get_near_data(int x, int y);
	int set_pixel_data(int x, int y, unsigned char value);
	unsigned int* create_pane(){return new unsigned int[width * height / intSize + 1];}
	bool free_clip(Clip* cl);
	Clip copy_clip(IPoint center, int radius, int from_layer = 0);//원을 둘러싼 정사각형을 클립한다.
	void paste_clip(Clip* cl, int to_layer = 0);
	int paste_clip(Clip* source, Clip* destination, bitOperation option);
	IPoint bit_arc(Clip* cl, IPoint center, float angle_from, float angle_to);
	
private:
	float bit_line(Clip* cl, IPoint center, float theta);
	int flat_line(unsigned int* pane, IPoint start_point, int longevity);
	int flat_line(Clip* pane, IPoint start_point, int longevity);
	enum bitOption {SUBST, OR, AND, XOR, MINUS, NOT};
	int find_num(int* array, int value, int size_of_array);
	int find_big(int* array, int size_of_array);
};
