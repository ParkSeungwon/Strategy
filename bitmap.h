struct IPoint {
	int x,y;
};

class Clip 
{
public:
	size_t **clip;
	IPoint lower_left;//lower left array의 비트맵에서의 uint 좌표
	int width, height;//width is * intSize

	Clip(IPoint center, int radius);//원을 포함하는 직사각형 영역
	Clip(IPoint lower_left, int width, int height);//직사각형 영역, 반드시 u_int형의 크기에 맞춤, basic
	Clip(Clip &cl1, Clip &cl2, bitOperation op);//두 개의 클립을 조인해서 만든다.
	Clip(Clip &cl, IPoint center, int radius);//다른 클립의 영역을 카피해서 만든다.
	Clip(Clip &cl) {this = new Clip(cl.lower_left, cl.width, cl.height;}
	~Clip();
	int clear();
	bool get_pixel(IPoint p);
	bool set_pixel(IPoint p, bool on_off);
	operator=(Clip &clip);
	int paste_from(Clip* source, bitOperation option);

	IPoint bit_circle(IPoint center, int radius);//클립된 후의 중심좌표
	IPoint bit_arc(IPoint center, float angle_from, float angle_to);
	IPoint bit_arc_circle(IPoint center, int radius_from, int radius_to, float angle_from, float angle_to);
	float bit_arc_line(IPoint center, int radius, float angle_from, float angle_to);

protected:
	int flat_line(IPoint starting_point, int length);
	float bit_line(IPoint center, float theta);//중심점을 지나는 직선을 기준으로 좌우를 비트마스크 처리
	enum bitOption {SUBST, OR, AND, XOR, MINUS, NOT};

private:
	bool boundary_check(IPoint p);

};

class Bitmap : public Clip
{
public:
	Clip *bitmap;
	int bit_per_pixel;
	
	Bitmap(int width, int height, int bpp);
	~Bitmap() {for(int i=0; i<bpp; i++) delete bitmap[i];}
	void clear() {for(int i=0; i<bit_per_pixel; i++) bitmap[i].clear();}
	
protected:
	int get_pixel(IPoint p);
	void set_pixel(IPoint p, unsigned char value);
	
private:
};
