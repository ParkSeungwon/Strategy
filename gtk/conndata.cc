#include <iostream>
#include <cstdlib>
#include <memory>
#include <fstream>
#include <gtkmm.h>
#include "../mysql/mysqldata.h"
using namespace std;

#include "join.h"
#include "conndata.h"

ConnectPopup::ConnectPopup() : 
		label1("Host name :"), label2("email addr :"), label3("Password  :"),
        label4("Database  :"), label5("U can use ID:anony@anony, PASS:anony"),
        button1("Connect"), button2("Save"),
        button3("Delete"), button4("Exit"), button5("Join"),
        frame1("Choose one Connection")
{
    homefile = getenv("HOME");
    homefile += "/.strategy";
    
	ifstream f(homefile.c_str());
	if(!f.is_open()) {
		ofstream f(homefile.c_str());
		f << "www.db4free.net anony@anony anony dbddfree ";
	}
	f.close();
	
	    
	set_title("Connect Database");
    pRadioButton = NULL;
	set_default_size(300, -1);
	add(vBox1);
	radioButton();
    vBox1.pack_start(frame1);
    frame1.add(vBox2);
	vBox1.pack_start(hBox1);
	vBox1.pack_start(hBox2);
	vBox1.pack_start(hBox3);
	vBox1.pack_start(hBox4);
    vBox1.pack_start(label5);
	hBox1.pack_start(label1);
	hBox2.pack_start(label4);
	hBox3.pack_start(label2);
	hBox4.pack_start(label3);
	hBox1.pack_start(entry1);
	hBox2.pack_start(entry4);
	hBox3.pack_start(entry2);
	hBox4.pack_start(entry3);
    entry1.set_max_length(25);
    entry2.set_max_length(25);
    entry3.set_max_length(25);
	entry3.set_visibility(false);
    entry4.set_max_length(25);
	vBox1.pack_start(hBox5);
	hBox5.pack_start(button1);
	hBox5.pack_start(button2);
	hBox5.pack_start(button3);
	hBox5.pack_start(button4);
    hBox5.pack_start(button5);
	button1.signal_clicked().connect(sigc::mem_fun(*this, &ConnectPopup::on_connect_click));
    button2.signal_clicked().connect(sigc::mem_fun(*this, &ConnectPopup::on_save_click));
    button3.signal_clicked().connect(sigc::mem_fun(*this, &ConnectPopup::on_delete_click));
	button4.signal_clicked().connect(sigc::mem_fun(*this, &ConnectPopup::on_exit_click));
    button5.signal_clicked().connect(sigc::mem_fun(*this, &ConnectPopup::on_join_click));
    set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
    set_modal(true);
	show_all_children();
}

void ConnectPopup::radioButton() 
{
	ifstream file(homefile.c_str());
	const int MAX_CONNECT = 100;
	string host[MAX_CONNECT], user[MAX_CONNECT], pass[MAX_CONNECT], db[MAX_CONNECT];
	int i=0;
	while(file >> host[i]) {
		file >> user[i];
		file >> pass[i];
		file >> db[i];
		i++;
	}
	file.close();

    if(pRadioButton != NULL) delete [] pRadioButton;
	pRadioButton = new Gtk::RadioButton[i];
    Gtk::RadioButton::Group group;
	if(i != 0) group = pRadioButton[0].get_group();
    int j;
	for(j=1; j<i; j++) pRadioButton[j].set_group(group);
    for(j=0; j<i; j++) {
        pRadioButton[j].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &ConnectPopup::on_radio_click), j));
        pRadioButton[j].set_label(host[j] +" "+ user[j] +" "+ db[j]);
		vBox2.pack_start(pRadioButton[j]);
	}
    radioSelection = 0;
    this->show_all_children();
}

ConnectPopup::~ConnectPopup()
{
	delete [] pRadioButton;
}

void ConnectPopup::on_save_click()
{
    if (checkValid()) {
        ofstream file(homefile.c_str(), std::ios_base::app);
        file << entry1.get_text() << " ";
        file << entry2.get_text() << " ";
        file << entry3.get_text() << " ";
        file << entry4.get_text() << " ";
        file.close();
        radioButton();
        label5.set_label("--");
    }
    else label5.set_label("No space allowed!");
}

bool ConnectPopup::checkValid()
{
    if(noSpace(entry1.get_text()) && noSpace(entry2.get_text()) &&
        noSpace(entry3.get_text()) && noSpace(entry4.get_text()) )
        return true;
    else return false;
}

bool ConnectPopup::noSpace(string s)
{
    if(s.find(' ', 0) == string::npos) return true;
    else return false;
}

void ConnectPopup::on_radio_click(int whichButton)
{
    ifstream file(homefile.c_str());
    string s;
    int i = 0;
    while ( i++ < whichButton) {
        for (int j=0; j < 4; j++) file >> s;
    }
    file >> s; entry1.set_text(s);
    file >> s; entry2.set_text(s);
    file >> s; entry3.set_text(s);
    file >> s; entry4.set_text(s);
    file.close();
    radioSelection = whichButton;
}

void ConnectPopup::on_delete_click()
{
    ifstream infile;
    infile.open(homefile.c_str());
    ofstream outfile;
    outfile.open("/tmp/temp.cfg");
    string s, garbage;
   
    for (int i=0; i < radioSelection; i++) {
        for (int j=0; j < 4; j++) {
            infile >> s;
            outfile << s << " ";
        }
    }
    for (int j=0; j < 4; j++) infile >> garbage;
    while (infile >> s) outfile << s << " ";
    outfile.close();
    infile.close();
    std::remove(homefile.c_str());
    std::rename("/tmp/temp.cfg", homefile.c_str());
    std::remove("/tmp/temp.cfg");
    radioButton();
}

void ConnectPopup::on_connect_click()
{
    if(checkValid()) {
        string host = entry1.get_text();
        string user = entry2.get_text();
        string pass = entry3.get_text();
        string db = entry4.get_text();

		QueryData qd;
		qd.connect(host, "strategy", "strategy", db);//host, id, pass, database
		SqlData m;
		m = qd.select("Users", "email = '" + user + "' and password = '" + pass + "'");
		if(m.contents.empty()) label5.set_label("Invalid!");
		else hide();
    }
}

void ConnectPopup::on_join_click()
{
	string host = entry1.get_text();
	string user = entry2.get_text();
	string pass = entry3.get_text();
	string db = entry4.get_text();
	joinpopup = make_shared<JoinPopup>(host, user, pass, db);
    joinpopup->set_transient_for(*this);
	joinpopup->show();
}
