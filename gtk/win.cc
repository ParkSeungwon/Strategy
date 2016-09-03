#include <string>
#include <iostream>
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

Win::Win() : time(area),
   	bt1("OK"), bt2("cancel"), bt3("open"), bt4("connect"), 
	box2(Gtk::ORIENTATION_VERTICAL), label1("라벨") 
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
	box2.pack_start(label1, Gtk::PACK_SHRINK);
 //   cout << "높이 " << area.height << endl;
 //   area.set_size_request(area.width, area.height);
    box1.pack_start(area);
    bt1.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_button_click));
    bt2.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_cancel_click));
    bt3.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_open_click));
	bt4.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_connect_click));
    show_all_children();
}

bool Win::on_button_press_event(GdkEventButton* e)
{
	label_change(e->x, area.get_height() - e->y - 1, e->button);
}

bool Win::on_key_press_event(GdkEventKey* e)
{
	cout << "key : " << e->keyval << endl;
	label1.set_text(to_string(e->keyval) + user);
	return false;
}

int Win::label_change(int x, int y, int bt)
{
	string s = Terrain::name[static_cast<int>(time.get_terrain_type(Point(x, y)))];
	s += "\n" + to_string(x);
	s += "\n" + to_string(y);
	s += "\n" + to_string(bt);
	label1.set_text(s);
	return s.size();
}

void Win::on_open_click()
{
	Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);

	//Add filters, so that only certain file types can be selected:

	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Map files");
	filter_any->add_pattern("*.map");
	dialog.add_filter(filter_any);
	//Show the dialog and wait for a user response:
	int result = dialog.run();

	//Handle the response:
	if(result == Gtk::RESPONSE_OK) {
		std::cout << "Open clicked." << std::endl;

		//Notice that this is a std::string, not a Glib::ustring.
		std::string filename = dialog.get_filename();
		std::cout << "File selected: " <<  filename << std::endl;
		teamsetup = make_shared<TeamSetup>(time.init_map(area.open_map_file(filename)));
		teamsetup->show();
    }
}

void Win::on_button_click()
{
	area.clear_map();
	area.paste_pix(100 + i_++, 1900, "units/Americans/bomber_hb.png", 1 + f_++);
	area.paste_pix(500, 1900, "units/Chinese/battlecruiser.png", M_PI);
	//ts = new TeamSetup(8);
    // force our program to redraw the entire clock.
	area.refresh();
	for(int i=0; i<100; i++) time.time_pass();
}

void Win::on_cancel_click()
{
//	Unit u{"bomber_hb"};
//	time.deployUnit(u, {800, 800}, 1.0);
//	time.deployedUnits[0]->insert_waypoint(100, 20, 50);
	for(int i=0; i<50; i++) time.time_pass();
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
	connectpopup = make_shared<ConnectPopup>();
	connectpopup->show();
}

void Win::set_user(string user)
{
	this->user += user;
}


