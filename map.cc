#include <algorithm>
#include "Weapon.h"
#include "Terrain.h"
#include "map.h"
#include "bitmap.h"
#include "Unit.h"
#include "Util.h"
#define TERRAIN_COUNT 14
typedef unsigned char UC;
using namespace Glob;

Map::Map(int w, int h, size_t *image, int ally)
{
	width = w;
	height = h;
	recon_bitmap = new Bitmap(w, h, ally);
	terrain_bitmap = new Bitmap(w, h, get_log2(TERRAIN_COUNT));
	city_bitmap = new Bitmap(w, h, get_log2(count_cities(image)));
	
	Bitmap *t = terrain_bitmap;
	Bitmap *c = city_bitmap;
	Point p;
	City ct;
	size_t dot = 0;

	for(size_t y = 0; y < h; y++) {
		for(size_t x = 0; x < w; x++) {
			p.x = x; p.y = y;
			t->set_pixel(p, (int)Terrain::get_terraintype_by_color(image[y * w + x]));
			if(image[y * width + x] & 0xff == 0xff) {//생산가능한 지형은 모두 블루값이 0xff임.
				dot = (image[y * width + x] & 0xff00) >> 2;
				c->set_pixel(p, dot);//도시의 고유번호를 부여함green
			}
		}
	}
}

int Map::occupy(Point p, int team)
{
	auto it = find(cities.begin(), cities.end(), city_bitmap->get_pixel(p));
	if(it != cities.end()) it->owner = team;
}

int Map::count_cities(size_t *image)
{
	Point p;
	size_t dot = 0;
	City ct;
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			p.x = x; p.y = y;
			if(image[y * width + x] & 0xff == 0xff) {//생산가능한 지형은 모두 블루값이 0xff임.
				dot = (image[y * width + x] & 0xff00) >> 2;
				if (find(cities.begin(), cities.end(), dot) == cities.end()) {//operator==구현 
					ct.identifier = dot;
					cities.push_back(ct);
				}
			}
		}
	}
	return cities.size();
}

bool Map::in_city(Point p) 
{
	 return city_bitmap->get_pixel(p);
}

City& Map::get_city(Point p) 
{
	int id = city_bitmap->get_pixel(p);
	return *find(cities.begin(), cities.end(), id);
}
	

int Map::geo_effect(Unit& u)
{
	TerrainType tt = get_terrain_type(u);
	UnitType ut = u.get_unit_type();
	u.set_evadeRatio(Terrain::get_evade_bonus(tt, ut));
	//supply
	bool ok = false;
	City& c = get_city(u);
	if(in_city(u)) {
		if(tt == TerrainType::city || tt == TerrainType::capital) {
			if(ut == UnitType::Armor || ut == UnitType::Infantry) ok = true;
		} else if(tt == TerrainType::airport && ut == UnitType::Air) ok = true;
		else if(tt == TerrainType::harbor && ut == UnitType::Ship) ok = true;
		
		if(ok && c.ally == u.get_ally()) {
			u.set_supply();
			u.set_recruit();
		}
		if(u.in_city()) occupy(u, u.get_team());
	} else u.out_of_city();

	if(ut == UnitType::Air && u.get_fuel() <= 0) {
		if(tt != TerrainType::airport || c.ally != u.get_ally()) 
			u.set_currentHealth(-100);
	}
}
		
	
Map::~Map()
{
	delete terrain_bitmap;
	delete recon_bitmap;
	delete city_bitmap;
}

void Map::deployUnit(Unit &u, Point p, float h) 
{
	City& c = get_city(p);
	u.set_team(c.owner);
	
	if(u.get_team() != 0) {//verify
		u.heading_toward = h;
		u.x = p.x; u.y = p.y;
		std::shared_ptr<Unit> up(new Unit(u));
		deployedUnits.push_back(up);
	}
}

int Map::generate_recon_bitmap() const
{
	Clip *cl;
	recon_bitmap->clear();
	for(auto& au : deployedUnits) {
		cl = new Clip((Point)*au, au->get_intelligenceRadius());
		cl->bit_circle((Point)*au, au->get_intelligenceRadius());//generate circle bit clip
		recon_bitmap->bitmap[au->get_ally()]->paste_from(cl, OR);//paste to get_team()team(i)'s layer
		delete cl;
	}
	int a;
	for(auto& d : deployedUnits) {
		a = d->get_ally();
		for(int i=0; i < recon_bitmap->bit_per_pixel; i++) {
			if(a != i) d->set_known_to(i, recon_bitmap->bitmap[i]->get_pixel(*d));
		//	else d->known_to[i] = true;
		}
	}
	return 0;
}

int Map::get_log2(int cc)
{
	int i=1;//to get log 2 cc
	for (int j=2; j<cc; j *= 2) i++;
	return i;
}

TerrainType Map::get_terrain_type(Point p) const
{
	return static_cast<TerrainType>(terrain_bitmap->get_pixel(p));
}

float Map::calculate_terrain_penalty(Unit& u, int time) const
{ //지형의 영향력을 고려한다. 호를 100개 내지 일정한 개수의 점으로 나누어서 각 점의 지형을 샘플로 뽑아 속도를 계산한다.
	float f, elapse = 0;
	int i, t = time;
	UnitType ut = u.get_unit_type();
	u.save();
	for(i=0; i < t*10; i++) {
		u.WhereAbout::time_pass(0.1 * i);//important casting 
		f = Terrain::get_move_penalty(get_terrain_type(u), ut);
		if(f == 0)  break;
		else elapse += 0.1 * f;
		if(elapse >= t*10) break;
	}
	u.restore();	
	return (float)i / (10 * t);
}

float Map::calculate_terrain_penalty(Unit& u) const 
{
	u.save();
	u.WhereAbout::operator=(u.waypoints[u.get_cur_waypt()]);
	float p = calculate_terrain_penalty(u, u.get_cur_time_in_waypt() + OneTick);
	u.restore();	
	return p;
}

