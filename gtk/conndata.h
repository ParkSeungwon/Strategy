#pragma once
#include <string>
class JoinPopup;

class ConnectPopup : public Gtk::Window {
private:
    int radioSelection;
    bool checkValid();
	bool noSpace(std::string s);
	std::string homefile;
    
protected:
	Gtk::VBox vBox1, vBox2;
	Gtk::HBox hBox1, hBox2, hBox3, hBox4, hBox5;
	Gtk::Entry entry1, entry2, entry3, entry4;
	Gtk::Label label1, label2, label3, label4, label5;
	Gtk::Button button1, button2, button3, button4, button5;
	Gtk::RadioButton *pRadioButton;
    Gtk::Frame frame1;

	virtual void on_save_click();
	virtual void on_delete_click();
	virtual void on_connect_click();
	virtual void on_exit_click() {hide();}
	virtual void on_radio_click(int whichButton);
    virtual void on_join_click();

    void radioButton();
    
public:
	std::shared_ptr<JoinPopup> joinpopup;
	ConnectPopup();
	~ConnectPopup();
};
