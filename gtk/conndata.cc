#include <iostream>
#include <functional>
#include <cstdlib>
#include <memory>
#include <fstream>
#include "mysqldata.h"
#include "join.h"
#include "conndata.h"
using namespace std;

ConnectPopup::ConnectPopup(string prog_id, string prog_pass) 
	: frame("Choose one Connection")
{
    homefile = getenv("HOME");
    homefile += "/." + prog_id;
	this->prog_id = prog_id;
	this->prog_pass = prog_pass;
	init_radio();
	pack_all();
}

void ConnectPopup::init_radio() 
{
	ifstream f(homefile.c_str());
	array<string, 4> s;
	int i = 0;
	while(f >> s[0] >> s[1] >> s[2] >> s[3]) {
		v_radio.push_back(Gtk::RadioButton(s[0] + ' ' + s[1] + ' ' + s[3]));
		v_radio.back().signal_clicked().connect(
				bind(&ConnectPopup::on_radio_click, this, i++, s));
	}
	Gtk::RadioButton::Group group;
	for(auto& a : v_radio) {
		radioBox.pack_start(a);
		a.set_group(group);
		a.set_active();
	}
	radioSelection = i-1;
}

void ConnectPopup::pack_all() 
{
	set_title("Connect Database");
	set_default_size(300, -1);

	Gtk::Box* box = get_content_area();
    box->pack_start(frame);
    frame.add(radioBox);
	for(int i=0; i<4; i++) {
		box->pack_start(hBox[i]);
		hBox[i].pack_start(label[i]);
		hBox[i].pack_start(entry[i]);
		entry[i].set_max_length(25);
	}
	box->pack_end(message_label);
	entry[2].set_visibility(false);
	label[0].set_label("Host name :");
	label[1].set_label("email addr :");
	label[2].set_label("Password  :");
	label[3].set_label("Database  :");
	message_label.set_label("U can use ID:anony@anony, PASS:anony");
	add_button("Connect", 1);
	add_button("Save", 2);
	add_button("Delete", 3);
	add_button("Exit", 4);
	add_button("Join", 5);

    set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
    set_modal(true);
	show_all_children();
}

void ConnectPopup::save()
{
    if (checkValid()) {
        ofstream file(homefile.c_str(), std::ios_base::app);
        for(int i=0; i<4; i++) file << entry[i].get_text() << ' ';
        message_label.set_label("--");
    } else message_label.set_label("No space allowed!");
}

bool ConnectPopup::checkValid()
{
    for(int i=0; i<4; i++) if(!noSpace(entry[i].get_text())) return false;
	return true;
}

bool ConnectPopup::noSpace(string s)
{
    if(s.find(' ', 0) == string::npos) return true;
    else return false;
}

void ConnectPopup::on_radio_click(int whichButton, array<string, 4> s)
{
	for(int i=0; i<4; i++) entry[i].set_text(s[i]);
    radioSelection = whichButton;
}

void ConnectPopup::del()
{
    ifstream infile(homefile.c_str());
    ofstream outfile("/tmp/temp.cfg");
    string s;
   
    for (int i=0; i < 4*radioSelection; i++) {
		infile >> s;
		outfile << s << ' ';
    }
    for (int i=0; i < 4; i++) infile >> s;
    while (infile >> s) outfile << s << ' ';
    outfile.close();
    infile.close();
    std::remove(homefile.c_str());
    std::rename("/tmp/temp.cfg", homefile.c_str());
    std::remove("/tmp/temp.cfg");
}

string ConnectPopup::connect()
{
    if(checkValid()) {
        string host = entry[0].get_text();
        string user = entry[1].get_text();
        string pass = entry[2].get_text();
        string db = entry[3].get_text();

		SqlQuery qd;
		qd.connect(host, prog_id, prog_pass, db);//host, id, pass, database
		qd.select("Users", "where email = '" + user + "' and password = '" + qd.password(pass) + "'");
		if(qd.empty()) return "";
		else return qd.begin()->front();
	}
}

void ConnectPopup::on_join_click()
{
	string host = entry[0].get_text();
	string user = entry[1].get_text();
	string pass = entry[2].get_text();
	string db = entry[3].get_text();
}

string repeat_dialog(string prog_id, string prog_pass)
{
	ConnectPopup cp(prog_id, prog_pass);
	int result = cp.run();
	switch(result) {
	case 1: return cp.connect();
	case 2: cp.save(); return "";
	case 3: cp.del(); return "";
	case 4: return "exit";
	case 5: return "";
	case Gtk::RESPONSE_DELETE_EVENT: return "exit";
//		JoinPopup jp();
	}
}
	
string login(string prog_id, string prog_pass)
{
	string s = "";
	while(s == "") s = repeat_dialog(prog_id, prog_pass);
	return s;
}


