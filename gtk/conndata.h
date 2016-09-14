#pragma once
#include <gtkmm.h>
#include <string>
class JoinPopup;
std::string login(std::string prog_id, std::string prog_pass, 
		std::string message = "U can use ID:anony@anony, PASS:anony");

class ConnectPopup : public Gtk::Dialog 
{
public:
	ConnectPopup(std::string prog_id, std::string prog_pass,
			std::string msg = "U can use ID:anony@anony, PASS:anony");
	std::string save();
	std::string del();
	std::string join();
	std::string connect();
    
protected:
	Gtk::VBox radioBox;
	Gtk::HBox hBox[4];
	Gtk::Entry entry[4];
	Gtk::Label label[4], message_label;
    Gtk::Frame frame;

	void on_radio_click(int whichButton, std::array<std::string ,4> s);
    
private:
    void init_radio();
	void pack_all();
	std::string join_dialog();

    int radioSelection;
	std::string prog_id, prog_pass;
	std::vector<Gtk::RadioButton> v_radio;
    bool checkValid();
	bool noSpace(std::string s);
	std::string homefile;
};

