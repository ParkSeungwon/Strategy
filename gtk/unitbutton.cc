#include"unitbutton.h"
#include"darea.h"
#include"src/Terrain.h"
#include"src/Unit.h"
#include<unordered_map>
using namespace std;

UnitButton::UnitButton(string nation, string unitname) {
	img = Darea::get_icon(nation, unitname);
	set_image(img);
}

void UnitButton::set_img(string nation, string unitname) {
	img = Darea::get_icon(nation, unitname);
	set_image(img);
	img.show();
	show_all_children();
}

Produce::Produce(const City& city) 
{
	auto tt = city.ttype();
	string nt = city.nation();
	cout << nt << endl;
	int t;
	if(tt == Glob::TerrainType::capital || tt == Glob::TerrainType::city) t = 1;
	else if(tt == Glob::TerrainType::harbor) t = 3; 
	else if(tt == Glob::TerrainType::airport) t = 0;
	for(auto& a : Unit::unit_def) {
		int k = a[10];
		switch(k) { //0 air 1 armor 2 infantry 3 ship
		case 0: case 3: 
			if(a[0] == nt && t == k) {
				icons.push_back(UnitButton(nt, a[1])); 
				icons.back().signal_clicked().connect(
						bind(&Produce::on_click, this, a[1]));
			}
			break;
		case 1: case 2: 
			if(a[0] == nt && t == 1) {
				icons.push_back(UnitButton(nt, a[1])); 
				icons.back().signal_clicked().connect(
						bind(&Produce::on_click, this, a[1]));
			}
		}
	}
	Gtk::Box* box = get_content_area();
	for(auto& a : icons) box->add(a);
	show_all_children();
}

void Produce::on_click(string s)
{
	selection = s;
	hide();
}

string produce(const City& city) {
	Produce pd(city);
	int result = pd.run();
	return pd.selection;
}
