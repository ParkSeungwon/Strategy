#include <iostream>
using namespace std;
#include <gtkmm.h>
#include "join.h"
#include "../mysql/mysqldata.h"

JoinPopup::JoinPopup(string host, string user, string pass, string db)
    :label1("email :"), label2("Nickname :"), label3("tel  :"), label4("password :"),
     label5("retype :"), button1("Join"), button2("Exit"), label_message("---")
{
    set_title("Join");
	this->host = host;
	this->db = db;
	this->user = user;
	this->pass = pass;
    add(vbox1);
    vbox1.pack_start(hbox1);
    vbox1.pack_start(hbox2);
    vbox1.pack_start(hbox3);
		 
    vbox1.pack_end(label_message);
    vbox1.pack_end(hbox_button);
	vbox1.pack_end(hbox5);
	vbox1.pack_end(hbox4);
		 
    hbox1.pack_start(label1);
    hbox1.pack_start(entry1);
	entry1.set_text(user);
    hbox2.pack_start(label2);
    hbox2.pack_start(entry2);
    hbox3.pack_start(label3);
    hbox3.pack_start(entry3);
    
    hbox4.pack_start(label4);
    hbox4.pack_start(entry4);
	entry4.set_text(pass);
	entry5.set_text(pass);
    hbox5.pack_start(label5);
    hbox5.pack_start(entry5);
	hbox_button.pack_start(button1);
	hbox_button.pack_start(button2);
		 
    set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
	entry4.set_visibility(false);
	entry5.set_visibility(false);
	entry1.set_max_length(30);
	entry2.set_max_length(30);
	entry3.set_max_length(30);
	entry4.set_max_length(30);
	entry5.set_max_length(30);
    label1.set_size_request(100);
    label2.set_size_request(100);
    label3.set_size_request(100);
    label4.set_size_request(100);
    label5.set_size_request(100);
    set_modal(true);

    button1.signal_clicked().connect(sigc::mem_fun(*this, &JoinPopup::on_join_click));
    button2.signal_clicked().connect(sigc::mem_fun(*this, &JoinPopup::on_exit_click));
    
    show_all_children();
}

void JoinPopup::on_join_click()
{
    string e = entry1.get_text();
    string p = vGetCurPass();
    string n = entry2.get_text();
    string t = entry3.get_text();
    string np = vGetNewPass();
	if(entry4.get_text() != entry5.get_text()) {
		label_message.set_label("password does not match!");
	}
    else {
		SqlData member;
		member.structure =  {
			{"email", "char(30) NOT NULL"},
			{"password", "char(45) DEFAULT NULL"},
			{"level", "tinyint(4) DEFAULT NULL"},
			{"name", "varchar(45) DEFAULT NULL"},
			{"tel", "varchar(20) DEFAULT NULL"},
			{"date", "datetime NOT NULL"}
		};
		member.table_name = "Users";
		member.extra = "primary key (email, date)";
		member.engine = "ENGINE=MyISAM DEFAULT CHARSET=utf8";
		
		QueryData qd;
		qd.connect(host, "strategy", "strategy", "strategy");//host, id, pass, database
		qd.create_table(member);
		SqlData s = qd.select("Users", "email = '" + e + "'");
		if(s.contents.empty()) {
			member.contents = {e, p, "1", n, t, qd.now()};
			qd.insert(member);
			label_message.set_label("Done! click Exit to login.");
		} else label_message.set_label("email exists!");
	}
}

string JoinPopup::vGetNewPass() {
    return "";
}
string JoinPopup::vGetCurPass() {
	return entry4.get_text();
}
string ChangeAccount::vGetCurPass() {
	return entry6.get_text();
}
string ChangeAccount::vGetNewPass() {
    return entry4.get_text();
}

ChangeAccount::ChangeAccount(string email, string name, string tel)
    : JoinPopup("", email, "", ""), label6("current password:")
{
    set_title("change account information");
    button1.set_label("change");
	label4.set_label("new password:");
    entry1.set_text(email);
    entry3.set_text(tel);
    entry2.set_text(name);
    vbox1.pack_start(hbox6);
    hbox6.pack_start(label6);
    hbox6.pack_start(entry6);
    entry6.set_visibility(false);
	entry6.set_max_length(30);
    label6.set_size_request(100);
    entry1.set_editable(false);
    //set_position(Gtk::WIN_POS_CENTER);
    //set_modal(true);
    show_all_children();
}
