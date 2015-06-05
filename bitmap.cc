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
	if(s.y < 0 || s.y >= height) return -1;
	if(s.x < 0) {
		l += s.x;
		s.x = 0;
	}
	if(s.x + l >= width) l = width - s.x + 1;//바운더리 체크
	
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

unsigned int** Bitmap::bit_circle(IPoint c, int r)
{
	unsigned int** pane = create_pane();
	IPoint s;
	for(s.y = c.y - r; s.y <= c.y + r; s.y++) {
		if(s.y >= 0 && s.y < height) {
			s.x = c.x - sqrtf(r*r - (c.y-s.y)*(c.y-s.y));
			flat_line(pane, s, 2*(s.x-c.x) +1);
		}
	}
	return pane;
}

Clip* Bitmap::create_clip(IPoint c, int r, int layer)
{
	Clip cl;
	if(c.x - r < 0) cl.x = 0;
	else cl.x = (c.x - r) / intSize;
	if(c.y - r < 0) cl.y = 0;
	else cl.y = c.y - r;
	if(c.y + r >= height) array_height = height - cl.x
	else array_height = 2 * r;
	if(c.x + r >= width) array_width = width / intSize - cl.x / intSize;
	else array_width = (c.x + r) / intSize - cl.x / intSize;//boundary check
	
	cl.clip = new unsigned int*[height];
	for(int y = 0; y <= array_height; y++) {
		cl.clip[y] = new unsigned int[array_width];
	}
	
	for(int y = 0; y <= array_height; y++) {
		for(int x = 0; x <= array_width; x++) {
			cl.clip[y][x] = bitmap[layer][y + cl.y][x + cl.x]; 
		}
	}
	return &cl;
}

void Bitmap::paste_clip(Clip* cl, int layer)
{
	for(int y = 0; y <= cl->height; y++) {
		for(int x = 0; x <= cl->width; x++) {
			bitmap[layer][y + cl.y][x + cl.x] = cl.clip[y][x]; 
		}
	}
}

unsigned int* Map::make_arc_bitmap(CGPoint c, float sa, float ea)
{
	
}

unsigned int* Util::bitOperation(unsigned int *bitmaskA, unsigned int *bitmaskB, bitOperation option) {
	int i;
	//if(*bitmaskA != *bitmaskB) throw 1;
	unsigned int *bitmaskOR = (unsigned int*)malloc(bitSize);
	while(i++ < bitSize) {
		switch option {
			case OR:
				*bitmaskOR = *bitmaskA | *bitmaskB; break;
			case AND:
				*bitmaskOR = *bitmaskA & *bitmaskB; break;
			case XOR:
				*bitmaskOR = *bitmaskA ^ *bitmaskB; break;
		}
		bitmaskOR++; bitmaskA++; bitmaskB++;
	}
	return bitmaskOR;
}

unsigned int* Map::bitmask(CGPoint center, int radius) {	
	
	unsigned int *bitmask = (unsigned int*)malloc(bitSize);
	int x, y, bit=0;
	unsigned int i, *ptr = bitmask;
	
	while(y<height) {
		x = 0;
		while(x<width) {
			bit++;
			if((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) <= radius*radius) {
				i = i | (1 << (intSize-1-(bit%intSize)));
			}
			if(bit%intSize == intSize-1) {
				*ptr = i;
				ptr++;
				i =0 ;
			}
			x++;
		}
		y++;
	}
	return bitmask;
}

