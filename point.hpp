
template <class T> class Point {
public:
	T x,y;
	float operator - (Point<T> b) {return sqrtf((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));}//distance 
	float operator % (Point<T> a) {return arctanf((a.y - y) / (a.x - x));}//angle
	void operator = (Point<int> p) {x = (T)p.x; y = (T)p.y;}
	void operator = (Point<float> p) {x = (T)p.x; y = (T)p.y;}
	Point<T> polar_to_xy(T r, float theta);
};
