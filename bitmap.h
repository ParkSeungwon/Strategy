enum bitOption {SUBST, OR, AND, XOR, MINUS, NOT};

class Clip 
{
public:
	size_t **clip;
	Point<int> lower_left;//lower left array의 비트맵에서의 uint 좌표
	int width, height;//width is * intSize

	Clip(Point<int> lower_left, int width, int height);//직사각형 영역, 반드시 u_int형의 크기에 맞춤, basic
	Clip(Point<int> center, int radius);//원을 포함하는 직사각형 영역
	Clip(Clip &cl1, Clip &cl2, bitOption op);//두 개의 클립을 조인해서 만든다.
	Clip(Clip &cl, Point<int> center, int radius);//다른 클립의 영역을 카피해서 만든다.
	~Clip();
	void clear();
	bool get_pixel(Point<int> p);
	bool set_pixel(Point<int> p, bool on_off);
	int operator = (Clip &clip);
	int paste_from(Clip* source, bitOption option);

	Point<int> bit_circle(Point<int> center, int radius);//클립된 후의 중심좌표
	Point<int> bit_arc(Point<int> center, float angle_from, float angle_to);
	Point<int> bit_arc_circle(Point<int> center, int radius_from, int radius_to, float angle_from, float angle_to);
	float bit_arc_line(Point<int> center, int radius, float angle_from, float angle_to);

protected:
	int flat_line(Point<int> starting_point, int length);
	float bit_line(Point<int> center, float theta);//중심점을 지나는 직선을 기준으로 좌우를 비트마스크 처리
	float correct_angle(float angle);

private:
	bool boundary_check(Point<int> p);

};

class Bitmap : public Clip
{
public:
	Clip *bitmap[];
	int bit_per_pixel;
	
	Bitmap(int width, int height, int bpp);
	~Bitmap() {for(int i=0; i<bit_per_pixel; i++) delete bitmap[i];}
	void clear() {for(int i=0; i<bit_per_pixel; i++) bitmap[i]->clear();}
	
protected:
	int get_pixel(Point<int> p);
	void set_pixel(Point<int> p, unsigned char value);
	
private:
};
