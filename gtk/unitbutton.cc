#include"unitbutton.h"
#include"darea.h"
#include<unordered_map>
using namespace std;

UnitButton::UnitButton(string nation, string unitname) {
	img = move(Darea::get_icon(nation, unitname));
	set_image(img);
}
