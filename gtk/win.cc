#include <string>
#include <iostream>
#include <sstream>
#include "point.h"
#include "Terrain.h"
#include "win.h"
#include "terrain_data.h"
#include "Util.h"
#include "teamsetup.h"
#include "conndata.h"
#include "Unit.h"
#include"Time.h"
//using namespace Gtk;
using namespace std;
using namespace Glob;
Interface* pInterface;
extern MapInterface* mInterface;
extern TimeInterface* tInterface;
string produce(const City& city);

Win::Win() : bt1("OK"), bt2("cancel"), bt3("open"), bt4("connect"), 
	ubt("Chinese", "infantry"), box2(Gtk::ORIENTATION_VERTICAL), label1("라벨")
{
	pInterface = this;
    set_border_width(10);
    set_default_size(900, 900);
    add(box1);
    swin.add(area);
    swin.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
	box1.pack_start(box2, Gtk::PACK_SHRINK);
	box1.pack_start(swin);
    box2.pack_start(bt1, Gtk::PACK_SHRINK);
    box2.pack_start(bt2, Gtk::PACK_SHRINK);
    box2.pack_start(bt3, Gtk::PACK_SHRINK);
    box2.pack_start(bt4, Gtk::PACK_SHRINK);
	box2.pack_start(ubt, Gtk::PACK_SHRINK);
	box2.pack_start(label1, Gtk::PACK_SHRINK);
 //   cout << "높이 " << area.height << endl;
 //   area.set_size_request(area.width, area.height);
    box1.pack_start(area);
    bt1.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_button_click));
    bt2.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_cancel_click));
    //bt3.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_open_click));
	bt4.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_connect_click));
    show_all_children();
}

Terrain_data Win::open_map_file(string map)
{
	return area.open_map_file(map);
}

bool Win::on_button_press_event(GdkEventButton* e)
{
	label_change(e->x, area.get_height() - e->y - 1, e->button);
}

bool Win::on_key_press_event(GdkEventKey* e)
{
	cout << "key : " << e->keyval << endl;
	if(selected_unit) {
		switch(e->keyval) {
			case 65361: //left
				slc_turn++;
				if(slc_turn == 1) slc_turn = -1000;
				if(abs(slc_turn) < selected_unit->get_minTurn()) slc_turn = 0;
				break;
			case 65362: //up
				if(slc_spd < selected_unit->get_maxSpd()) slc_spd++; 
				break;
			case 65363: //right
				slc_turn--;
				if(slc_turn == -1) slc_turn = 1000;
				if(abs(slc_turn) < selected_unit->get_minTurn()) slc_turn = 0;
				break;
			case 65364: //down
				if(slc_spd > selected_unit->get_maxSpd()) slc_spd--;
				break;
			case 65293: //enter

			case 105://i
			case 100://d
			case 45://-
			case 61://=
			case 65379://insert
			case 65535://delete
			case 91://[
			case 93://]
			default:;
		}
		tInterface->sync();
	}
	label1.set_text(to_string(e->keyval) + user);
	return false;
}

int Win::label_change(int x, int y, int bt)
{
	stringstream ss;
	ss << Terrain::name[static_cast<int>(mInterface->get_terrain_type(Point(x, y)))];
	auto city = mInterface->get_city(Point(x,y));
	auto u = mInterface->getUnit(Point{x,y});
	ss << endl << x << endl << y << endl << bt << endl << city.nation();
	if(u) {
		selected_unit = u;
		ubt.set_img(u->nation(), u->get_unitName());
		slc_turn = 0;
		slc_spd = u->get_maxSpd();
		slc_dur = 0;
		ss << endl << u->get_unitName() << endl << "H : ";
		ss << u->get_currentHealth() << '/' << endl << "F : ";
		ss << u->get_fuel() << '/';
		u->insert_waypoint(30, 1, 500);
		u->insert_waypoint(80, 70, 100);
	} else if(bt == 3 && city.nation() != "") {
		string unit  = produce(city);
		mInterface->deployUnit(Unit{city.nation(), unit} + Weapon{"Aim-9"}, 
				Point{x,y}, 0);
	}
	label1.set_text(ss.str());
	tInterface->sync();
	return ss.str().size();
}


void Win::on_button_click()
{
	extern FieldInterface* fInterface;

	area.clear_map();
	fInterface->paste_pix(100 + i_++, 1900, "units/Americans/bomber_hb.png", 1 + f_++);
	//area.paste_pix(100 + i_++, 1900, "units/Americans/bomber_hb.png", 1 + f_++);
	//area.paste_pix(500, 1900, "units/Chinese/battlecruiser.png", M_PI);
	//ts = new TeamSetup(8);
    // force our program to redraw the entire clock.
	area.refresh();

	mInterface->deployUnit(Unit{"British", "bomber_hb"}, Point{1793,875}, 0);//if point is not city crash...
//	mInterface->deployedUnits[0]->insert_waypoint(-20, 5, 10);
	//for(int i=0; i<100; i++) time.time_pass();
}

void Win::on_cancel_click()
{
//	Unit u{"bomber_hb"};
//	time.deployUnit(u, {800, 800}, 1.0);
//	time.deployedUnits[0]->insert_waypoint(100, 20, 50);
	//for(int i=0; i<50; i++) time.time_pass();
	Glob::To_draw td;
	td.x = 300 + i_++*10;
	td.y = 300;
	td.rmin = 100;
	td.rmax = 100;
	td.angle_from = 0;
	td.angle_to = M_PI/2;
	td.color[0] = (i_%10)/10.0;
	td.color[1] = 0.4;
	td.color[2] = 0.0;
	td.color[3] = 0.2;

	area.insert_to_draw(td);
	area.refresh();
}

void Win::on_connect_click()
{
	extern TimeInterface* tInterface;
	for(int i=0; i<1000; i++) {
		tInterface->time_pass();
//		tInterface->sync();
	}
}

void Win::set_user(string user)
{
	this->user += user;
}


