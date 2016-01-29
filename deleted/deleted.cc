
	void set_headingToward(float f) {heading_toward = correct_angle(f);}
	float get_headingToward() {return heading_toward;}

void Bitmap::paste_clip(Clip* cl, int layer)
{
	for(int y = 0; y <= cl->height; y++) {
		for(int x = 0; x <= cl->width; x++) {
			if(cl.y + y >= 0 && cl.x + x >= 0 && cl.x + x < width && cl.y + y < height)
				bitmap[layer][y + cl.y][x + cl.x] = cl.clip[y][x]; 
		}
	}
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

float Unit::calculateMovableDistanceForPolar(float theta) 
{
    float relativeRadius = self.headingToward + theta;
    return (2 * maximumSpeed  * cosf(relativeRadius))/ (M_PI - 2 * relativeRadius);
    
}


//CGPoint Unit::getTurnCenter(CGPoint destination) 
//{
//    float a = positionInfo.position.x;
//    float b = positionInfo.position.y;
//    float c = destination.x;
//    float d = destination.y;
//   
//    float cota = 1/tanf(positionInfo.headingToward);
//    CGPoint center;
//    center.x = ( (b-d)/2+(a*a-c*c)/(2*(d-b)) ) / (cota+(a-c)/(d-b));
//    center.y = cota*(a-center.x)+b;
//    return center;
//}


//float Unit::getTurnRadius (CGPoint destination) 
//{
//    CGPoint center = getTurnCenter(destination);
//    return distanceBetween(destination, center);
//}

int Weapon::operator ++ (Unit e[])
{
	int v = 0, ret, h = 1000;
	for(int i=0; e[i] != NULL; i++) {
		if(*this + e[i] <= 0) break;
		switch(preference) {
			case HIGH_DAMAGE:
				if(v < *this + e[i]) {
					v = *this + e;
					ret = i;
				}
				break;
			case LOW_HEALTH:
				if(h < e[i].currentHealth) {
					h = e[i].currentHealth;
					ret = i;
				}
				break;
			case HIGH_RATIO:
				if(v > hitRate(e[i])) {
					v = hitRate(e[i]);
					ret = i;
				}
				break;
			case EXPENSIVE:
				if(v > e[i].unitPrice) {
					v = e[i].unitPrice;
					ret = i;
				}
				break;
			case CHEAP:
				if(h < e[i].unitPrice) {
					v = e[i].unitPrice;
					ret = i;
				}
		}
	}
	return ret;
}

int Waypoint::how_long_can_i_go(int start, int fuel) {
	Nth nth = nth_way(start);
	int tmp = fuel;
	int dur;
	fuel -= waypoints[nth.n].speed * (waypoints[nth.n].duration - nth.sec);
	while(fuel > 0) {
		tmp = fuel;
		dur += waypoints[nth.n].duration;
		fuel -= waypoints[++nth.n].duration * waypoints[nth.n].speed;
	}
	dur += tmp / waypoints[nth.n].speed;
	return start + dur;
}

int Waypoint::moved_distance(int start, int end) {
	Nth nth1 = nth_way(start);
	Nth nth2 = nth_way(end);
	int distance = 0;
	for(int i = nth1.n; i <= nth2.n; i++) {
		distance += waypoints[i].speed * waypoints[i].duration;
	}
	distance -= waypoints[nth1.n].speed * nth1.sec;
	distance -= waypoints[nth2.n].speed * (waypoints[nth2.n].duration - nth2.sec);
	return distance;
}

int Unit::operator >> (vector<Unit> enemy)
{
	int dice;
	for(auto& w : weapon) dice = w >> e;
	return dice;
}
		
int Unit::movable_line(Point<int> tc, int time, Clip *cl)
{//used by movable_area
	float start_angle = tc % position.to_int();
	
	save();
	speed = maximumSpeed;
	turn_center = tc;
	float angle_from = tc % position.to_int();
	Util::correct_angle(angle_from);
	time_pass(time);//call the time_pass of this Unit
	float angle_to = tc % position.to_int();
	Util::correct_angle(angle_to);
	float radius = tc ^ position.to_int();
	restore();
	
	if(angle_to >= angle_from) cl->bit_arc_line(tc, radius, start_angle, angle_to);
	else {
		cl->bit_arc_line(tc, radius, start_angle, 2 * M_PI);
		cl->bit_arc_line(tc, radius, 0, angle_to);
	}
	return radius * (angle_to - angle_from);
}

Clip* Unit::movable_area(int time)
{
	Clip *ret = new Clip(position.to_int(), maximumSpeed * time);
	Point<int> p;
	for(int r=minimumTurnRadius; r <= maximumSpeed * time * 10; r++) {//10? enough?
		for(int i=-1; i<= 1; i += 2) {//to calculate both side
			p = p.polar_to_xy(r, M_PI / 2 * i + heading_toward);
			p.x += position.x;
			p.y += position.y;
			movable_line(p, time, ret);//set_pixel이 OR로 작동함.
		}
	}
	return ret;
}
bool Unit::operator()(const Unit& u)
{
	if(u.currentHealth <= 0) return true;
	if(u.fuel <= 0 && u.unit_type == Air) return true;
	return false;
}
int Map::generate_weapon_range_bitmap() const
{
	Clip *cl;
	weapon_range_bitmap->clear();
	for(auto& u : deployedUnits) {
		for(auto& w : u->weapon) {
			cl = new Clip((Point)*u, w.get_shootingRangeMax());
			cl->bit_arc_circle((Point)*u, w.get_shootingRangeMin(), w.get_shootingRangeMax(), w.get_shootingAngleFrom(), w.get_shootingAngleTo());
			weapon_range_bitmap->bitmap[u->ally]->paste_from(cl, OR);
			delete cl;
		}
	}
	return 0;
}
int Map::count_cities(size_t **image)
{
	Point p;
	size_t dot = 0;
	City ct;
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			p.x = x; p.y = y;
			if(image[y][x] & 0xff == 0xff) {//생산가능한 지형은 모두 블루값이 0xff임.
				dot = (image[y][x] & 0xff00) >> 2;
				if (find(cities.begin(), cities.end(), dot) == cities.end()) {//operator==구현 
					ct.identifier = dot;
					cities.push_back(ct);
				}
			}
		}
	}
	return cities.size();
}
int Darea::copy_pixbuf(const Glib::RefPtr<Gdk::Pixbuf>& s, Glib::RefPtr<Gdk::Pixbuf>& d)
{
	int r, n, w, h;
	if(w = s->get_width() != d->get_width()) return -1;
	if(h = s->get_height() != d->get_height()) return -1;
	if(s->get_bits_per_sample() != d->get_bits_per_sample()) return -2;
	if(n = s->get_n_channels() != d->get_n_channels()) return -3;
	if(s->get_colorspace() != d->get_colorspace()) return -4;
	if(s->get_has_alpha() != d->get_has_alpha()) return -5;
	if(r = s->get_rowstride() != d->get_rowstride()) return -6;
	auto sp = s->get_pixels();
	auto dp = d->get_pixels();

	for(int y=0; y<h; y++) {
		for(int x=0; x<w; x++) {
			for(int i=0; i<4; i++) (dp + y*r + x*n)[i] = (sp + y*r + x*n)[i];
		}
	}
	return 0;
}
void Darea::xy_to_polar(float& x, float& y)
{
	float r = sqrt(x*x + y*y);
	if(x == 0) {
		x = r;
		if(y > 0) y = M_PI / 2;
		else y = -M_PI / 2;
	} else {
		float theta = atan(y/x);
		if(x < 0) theta += M_PI;
		x = r;
		y = theta;
	}
}

void Darea::polar_to_xy(float& r, float& theta)
{
	float x = r * cos(theta);
	float y = r * sin(theta);
	r = x;
	theta = y;
}

void Darea::rotate(float& x, float& y, float rad)
{
	xy_to_polar(x, y);
	y += rad;
	polar_to_xy(x, y);
}

Terrain_data Darea::return_terrain_data()
{
	Terrain_data td;
	td.w = terrain->get_width();
	td.h = terrain->get_height();
	int r = terrain->get_rowstride();
	int n = terrain->get_n_channels();
	unsigned char* p = terrain->get_pixels();
	unsigned char* q;
	td.tmap = new size_t[td.h * td.w];
	size_t tmp, dot;
	for(int y=0; y<td.h; y++) {
		for(int x=0; x<td.w; x++) {
			q = p + y * r + x * n;
			tmp = q[0];
		   	tmp << 24;
			dot = tmp;
			tmp = q[1];
			tmp << 16;
			dot |= tmp;
			tmp = q[2];
			tmp << 8;
			dot |= tmp;
			tmp = q[3];
			dot |= tmp;
			td.tmap[y*td.w + x] = dot; 
		}
	}
	return td;
}

Terrain_data::Terrain_data(Terrain_data&& tr)
{
	w = tr.w;
	h = tr.h;
	tmap = tr.tmap;
	tr.tmap = nullptr;
}

Terrain_data& Terrain_data::operator=(Terrain_data&& tr)
{
	w = tr.w;
	h = tr.h;
	delete tmap;
	tmap = tr.tmap;
	tr.tmap = nullptr;
	return *this;
}

Terrain_data::~Terrain_data()
{
	if(tmap != nullptr) delete [] tmap;
}
int Map::get_log2(int cc)
{
	int i=1;//to get log 2 cc
	for (int j=2; j<cc; j *= 2) i++;
	return i;
}

