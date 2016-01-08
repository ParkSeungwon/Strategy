
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

