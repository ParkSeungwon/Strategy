Bitmap::Bitmap(int bpp)
{
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

int Bitmap::flat_line(Clip* cl, IPoint s, int l)
{
	//boundary check
	if(s.y < 0 || s.y >= cl->array_height || l <= 0) return -1;
	if(s.x < 0) s.x = 0;
	if(s.x + l >= cl->array_width * intSize) l = cl->array_width * intSize - s.x;
	
	//use coordinate of clip
	unsigned int mask;
	int rest = s.x % intSize;
	if(l < intSize - rest) {
		mask = 0xffffffff << (intSize - l);
		mask = mask >> rest;
		cl->clip[s.y][s.x / intSize] = mask;
	} else {
		mask = 0xffffffff >> rest;
		cl->clip[s.y][s.x / intSize] = mask;
		l -= intSize - rest;//앞에서 쓴 부분의 비트맵을 뺀다.
		rest = l % intSize;
		int i;
		for(i=1; i <= l/intSize; i++) cl->clip[s.y][s.x / intSize + i] = 0xffffffff;
		mask = 0xffffffff << (intSize - rest);
		cl->clip[s.y, s.x / intSize + i] = mask;
	}
	return l / intSize;
}

IPoint Bitmap::bit_circle(Clip *cl, IPoint c, int r)
{
	c.x -= intSize * cl->x;
	c.y -= cl->y;
	IPoint s;
	for(s.y = c.y - r; s.y <= c.y + r; s.y++) {
		s.x = c.x - sqrtf(r*r - (c.y-s.y)*(c.y-s.y));
		flat_line(cl, s, 2*(s.x-c.x) +1);
	}
	return c;
}

float Bitmap::bit_line(Clip* cl, IPoint c, float theta)//if theta is over PI, right area of  the line
{
	theta = correct_angle(theta);
	c.x -= cl.x * intSize;
	c.y -= cl.y;
	float tan = tanf(theta);
	int l;
	for(int y = 0; y < cl->y; y++) {
		l = c.x - (y - c.y) / tan;
		if(theta < M_PI) flat_line(cl, 0, l);
		else flat_line(cl, l, cl->array_width * intSize - l);
	}
	return tan;
}

IPoint Bitmap::bit_arc(Clip* cl, IPoint c, float fr, float to)
{
	c.x -= cl->x * intSize;
	c.y -= cl->y;
	bit_line(cl, c, fr);
	Clip cl1 = create_clip(cl->x, cl->y, cl->array_width, cl->array_height);
	bit_line(&cl1, c, correct_angle(to + M_PI));
	if(to < from) to += 2 * M_PI;//한바퀴 도는 경우 고려
	if(to - from < M_PI) paste_clip(&cl1, cl, AND);
	else paste_clip(&cl1, cl, OR);
	free_clip(&cl1);
	return c;
}

IPoint Bitmap::bit_arc_circle(Clip* cl, IPoint c, int rf, int rt, float af, float at)
{
	c.x -= cl->x * intSize;
	c.y -= cl->y;
	bit_circle(cl, c, rt);
	Clip cl1 = create_clip(cl->x, cl->y, cl->array_width, cl->array_height);
	Clip cl2 = create_clip(cl->x, cl->y, cl->array_width, cl->array_height);
	bit_circle(&cl1, c, rf);
	bit_arc(&cl2, c, af, at);
	paste_clip(&cl1, cl, MINUS);
	paste_clip(&cl2, cl, AND);
	free_clip(&cl1);
	free_clip(&cl2);
	return c;
}

Clip Bitmap::join_clip(Clip *cl1, Clip *cl2, bitOperation op)
{	
	//new clip region to include both clips
	int x = min(cl1.x, cl2.x);
	int y = min(cl1.y, cl2.y);
	int array_width = max(cl1.x + cl1.array_width * intSize, cl2.x + cl2.width * intSize) - cl.x;
	array_width = cl.array_width / intSize;
	int array_height = max(cl1.y + cl1.array_height, cl2.y + cl2.height) - cl.y;
	Clip cl = create_clip(x, y, array_width, array_height);
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

Clip Bitmap::create_clip(IPoint c, int r)
{
	return create_clip((c.x-r)/intSize, c.y-r, (2*r+1)/intSize, 2*r+1);
}

Clip Bitmap::create_clip(int x, int y, int width, int height)
{
	Clip cl;
	cl.x = x;
	cl.y = y;
	cl.width = width;
	cl.height = height;
	
	//memory allocation
	cl.clip = new unsigned int*[height];
	for(int y = 0; y < cl.array_height; y++) {
		cl.clip[y] = new unsigned int[cl.array_width];
	}
	return cl;
}

bool Bitmap::free_clip(Clip* cl) 
{
	for(int y = 0; y <= cl->array_height; y++) {
		delete [] cl->clip[y];
	}
	delete [] cl->clip;
	return true;
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

int Bitmap::paste_clip(Clip *source, Clip *dest, bitOperation op)
{
	int diffx = source->x - dest->x;
	int diffy = source->y - dest->y;
	for(int y = 0; y <= source->height; y++) {
		if(diffy + y >= 0 && diffy + y < dest->array_height) {
			for(int x = 0; x <= source->width; x++) {
				if(diffx + x >= 0 && diffx + x < dest->array_width) {
					switch op {
						case SUBST:
							dest->clip[y + diffy][x + diffx] = source->clip[y][x];
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


