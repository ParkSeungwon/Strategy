int Bitmap::alloc(int w, int h, int bpp)
{
	width = w;
	height = h;
	bitSize = width * height / sizeof(unsigned int) + 1;//
	intSize = 8 * sizeof(unsigned int);//bit of int=32
	
	bit_per_pixel = bpp;
	bitmap = new unsigned int**[bit_per_pixel];
	for(int i=0; i<bit_per_pixel; i++) {
		bitmap[i] = new unsigned int*[height];
		for(int y=0; y<width/intSize+1; y++) {
			bitmap[i][y] = new unsigned int[width/intSize+1];
		}
	}
	return (width/intSize+1) * h * bpp;
}

int Bitmap::clear()
{
	for(int i=0; i<bit_per_pixel; i++) {
		for(int y=0; y<height; y++) {
			for(int x=0; x*intSize<width; x++) {//be careful
				bitmap[i][y][x] = 0;
			}
		}
	}
	return x * y * i;
}

Bitmap::~Bitmap()
{
	for(int i = 0; i < bit_per_pixel; i++) {
		for(int x=0; x < width/intSize+1; x++) {
			delete [] bitmap[i][x];
		}
		delete [] bitmap[i];
	}
	delete [] bitmap;
}

int Bitmap::get_pixel_data(int x, int y)
{
	int shift = intSize - 1 - (x % intSize);
	unsigned int mask = 1 << shift;
	for(int i=0; i<bit_per_pixel; i++) {
		b = bitmap[i][y][x/intSize] & mask;
		b = b >> shift;
		ret += b << i;
	}
	return ret;
}

bool Bitmap::get_pixel_of_layer(int x, int y, int l)
{
	int shift = intSize - 1 - ( x % intSize );
	unsigned int mask = 1 << shift;
	if(bitmap[l][y][x/intsize] & mask == 0) return false;
	else return true;
}

int Bitmap::get_near_data(int x, int y)
{
	int ret[21 * 21];
	int repeat[21 * 21];
	int tmp;
	int n, k=0;
	for(int i=-10; i<=10; i++) {
		for(int j=-10; j<=10; j++) {
			tmp = get_pixel_data(x+i, y+j);
			n = find_num(ret, tmp, 21 * 21);
			if(n != -1) repeat[n]++;
			else ret[k++] = tmp;
		}
	}
	return ret[find_big(repeat, 21*21)];
}

int Bitmap::find_num(int* ar, int v, int s)
{
	for(int i=0; i<s; i++) {
		if(ar[i] == v) return i;
	}
	return -1;
}

int Bitmap::find_big(int *ar, int s)
{
	int index = 0;
	for(int i=0; i<s; i++) {
		if(ar[i] > ar[index]) index = i;
	}
	return index;
}

int Bitmap::set_pixel_data(int x, int y, unsigned char v)
{
	int shift = intSize - 1 - (x % intSize);
	unsigned int mask = 1 << shift;
	mask = mask & v;
	for(int i=0; i<bit_per_pixel; i++) {
		v = v << shift--;
		bitmap[i][y][x/intSize] = (bitmap[i][y][x/intSize] & ~mask) | (v & mask);
	}
	return mask;//쓸모없다
}

int Bitmap::flat_line(unsigned int** pane, IPoint s, int l)
{
	//boundary check
	if(s.y < 0 || s.y >= height) return -1;
	if(s.x < 0) {
		l += s.x;
		s.x = 0;
	}
	if(s.x + l >= width) l = width - s.x + 1;
	
	int ret = l;
	unsigned int mask;
	int rest = s.x % intSize;
	if(l < intSize - rest) {
		mask = 0xffffffff << (intSize - l);
		mask = mask >> rest;
		pane[s.y][s.x / intSize] = mask;
	} else {
		mask = 0xffffffff >> rest;
		pane[s.y][s.x / intSize] = mask;
		l -= intSize - rest;//앞에서 쓴 부분의 비트맵을 뺀다.
		rest = l % intSize;
		int i;
		for(i=1; i <= l/intSize; i++) pane[s.y][s.x / intSize + i] = 0xffffffff;
		mask = 0xffffffff << (intSize - rest);
		pane[s.y, s.x / intSize + i] = mask;
	}
	return ret;
}

int Clip::flat_line(IPoint s, int l)
{
	//boundary check
	if(s.y < 0 || s.y >= height || l <= 0) return -1;
	if(s.x < 0) s.x = 0;
	if(s.x + l >= width) l = width - s.x;
	
	//use coordinate of clip
	unsigned int mask;
	int rest = s.x % intSize;
	if(l < intSize - rest) {
		mask = 0xffffffff << (intSize - l);
		mask = mask >> rest;
		clip[s.y][s.x / intSize] = mask;
	} else {
		mask = 0xffffffff >> rest;
		clip[s.y][s.x / intSize] = mask;
		l -= intSize - rest;//앞에서 쓴 부분의 비트맵을 뺀다.
		rest = l % intSize;
		int i;
		for(i=1; i <= l/intSize; i++) clip[s.y][s.x / intSize + i] = 0xffffffff;
		mask = 0xffffffff << (intSize - rest);
		clip[s.y, s.x / intSize + i] = mask;
	}
	return l / intSize;
}

IPoint Clip::bit_circle(IPoint c, int r)
{
	c.x -= intSize * lower_left.x;
	c.y -= lower_left.y;
	IPoint s;
	for(s.y = c.y - r; s.y <= c.y + r; s.y++) {
		s.x = c.x - sqrtf(r*r - (c.y-s.y)*(c.y-s.y));
		flat_line(s, 2*(s.x-c.x) +1);
	}
	return c;
}

float Clip::bit_line(IPoint c, float theta)//if theta is over PI, right area of  the line
{
	theta = correct_angle(theta);
	c.x -= lower_left.x;
	c.y -= lower_left.y;
	float tan = tanf(theta);
	int l;
	for(int y = 0; y < lower_left.y; y++) {
		l = c.x - (y - c.y) / tan;
		if(theta < M_PI) flat_line(0, l);
		else flat_line(l, width * intSize - l);
	}
	return tan;
}

IPoint Clip::bit_arc(IPoint c, float fr, float to)
{
	c.x -= lower_left.x;
	c.y -= lower_left.y;
	bit_line(c, fr);
	Clip cl1 = create_clip(cl->x, cl->y, cl->array_width, cl->array_height);
	bit_line(&cl1, c, correct_angle(to + M_PI));
	if(to < from) to += 2 * M_PI;//한바퀴 도는 경우 고려
	if(to - from < M_PI) paste_clip(&cl1, cl, AND);
	else paste_clip(&cl1, cl, OR);
	free_clip(&cl1);
	return c;
}

IPoint Clip::bit_arc_circle(IPoint c, int rf, int rt, float af, float at)
{
	c.x -= lower_left.x;
	c.y -= lower_left.y;
	bit_circle(c, rt);
	Clip *cl1 = new Clip(lower_left, width, height);
	Clip *cl2 = new Clip(lower_left, width, height);
	bit_circle(cl1, c, rf);
	bit_arc(cl2, c, af, at);
	paste_clip(cl1, this, MINUS);
	paste_clip(cl2, this, AND);
	free_clip(cl1);
	free_clip(cl2);
	return c;
}

Clip* Clip::join_clip(Clip &cl1, Clip &cl2, bitOperation op)
{	
	//new clip region to include both clips
	int x = min(cl1.lower_left.x, cl2.lower_left.x);
	int y = min(cl1.lower_left.y, cl2.lower_left.y);
	int width = max(cl1.lower_left.x + cl1.width, cl2.lower_left.x + cl2.width) - cl.lower_left.x;
	width = cl.width / intSize;
	int height = max(cl1.lower_left.y + cl1.height, cl2.lower_left.y + cl2.height) - cl.lower_left.y;
	IPoint p; p.x = x; p.y = y;
	Clip *cl = new Clip(p, width, height);
	paste_clip(cl1, cl, SUBST);
	paste_clip(cl2, cl, op);
	return cl;
}

Clip Bitmap::copy_clip(IPoint c, int r, int layer)
{
	Clip cl = create_clip(c, r);
	
	//copy to clip
	for(int y = 0; y <= array_height; y++) {
		for(int x = 0; x <= array_width; x++) {
			if(cl.y + y >= 0 && cl.x + x >= 0 && cl.x + x < width && cl.y + y < height) 
				cl.clip[y][x] = bitmap[layer][y + cl.y][x + cl.x]; 
		}
	}
	return cl;
}

Clip* Clip::circle_clip(IPoint c, int r)
{
	IPoint p;
	p.x = c.x - r;
	p.y = c.y - r;
	Clip* cl = new Clip(p, (2*r+1)/intSize, 2*r+1);
	return cl;
}

Clip::Clip(IPoint p, int w, int h)
{
	int rest = p.x % intSize;
	p.x = p.x - share;
	this->lower_left = p;
	width =((w + share) / intSize + 1) * intSize;
	height = h;
	
	//memory allocation
	clip = new unsigned int*[height];
	for(int y = 0; y < height; y++) {
		clip[y] = new unsigned int[width/intSize];
	}
}

Clip::~Clip() 
{
	for(int y = 0; y < height; y++) {
		delete [] clip[y];
	}
	delete [] clip;
}

void Bitmap::paste_clip(Clip* cl, int layer)
{
	for(int y = 0; y <= cl->height; y++) {
		for(int x = 0; x <= cl->width; x++) {
			if(cl.y + y >= 0 && cl.x + x >= 0 && cl.x + x < width && cl.y + y < height)
				bitmap[layer][y + cl.y][x + cl.x] = cl.clip[y][x]; 
		}
	}
}

int Clip::paste_clip(Clip *source, Clip *dest, bitOperation op)
{
	int diffx = source->x - dest->x;
	int diffy = source->y - dest->y;
	for(int y = 0; y <= source->height; y++) {
		if(diffy + y >= 0 && diffy + y < dest->array_height) {
			for(int x = 0; x <= source->width; x++) {
				if(diffx + x >= 0 && diffx + x < dest->array_width) {
                    switch(op) {
						case SUBST:
							dest->clip[y + diffy][x + diffx] = source->clip[y][x];
                            break;
						case OR:
							dest->clip[y + diffy][x + diffx] = 
							dest->clip[y + diffy][x + diffx] | source->clip[y][x]; 
							break;
						case AND:
							dest->clip[y + diffy][x + diffx] = 
							clip[y + diffy][x + diffx] & source->clip[y][x];
							break;
						case XOR:
							dest->clip[y + diffy][x + diffx] = 
							clip[y + diffy][x + diffx] ^ source->clip[y][x];
							break;
						case MINUS:
							dest->clip[y + diffy][x + diffx] = 
							clip[y + diffy][x + diffx] & ~source->clip[y][x];
							break;
						case NOT:
							dest->clip[y + diffy][x + diffx] = ~source->clip[y][x];
							break;
					}
				}
			}
		}
	}
	return diffx * diffy;
}


