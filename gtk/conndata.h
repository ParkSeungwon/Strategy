#pragma once
#include <gtkmm.h>
#include <string>
class JoinPopup;
std::string login(std::string prog_id, std::string prog_pass);

class ConnectPopup : public Gtk::Dialog 
{
public:
	ConnectPopup(std::string prog_id, std::string prog_pass);
	void save();
	void del();
	std::string connect();
    
protected:
	Gtk::VBox radioBox;
	Gtk::HBox hBox[4];
	Gtk::Entry entry[4];
	Gtk::Label label[4], message_label;
    Gtk::Frame frame;

	void on_radio_click(int whichButton, std::array<std::string ,4> s);
    void on_join_click();

    
private:
    void init_radio();
	void pack_all();
    int radioSelection;
	std::string prog_id, prog_pass;
	std::vector<Gtk::RadioButton> v_radio;
    bool checkValid();
	bool noSpace(std::string s);
	std::string homefile;
};
