#pragma once
#include <string>

class JoinPopup : public Gtk::Window
{
protected:
    Gtk::Entry entry1, entry2, entry3, entry4, entry5;
    Gtk::Label label1, label2, label3, label4, label5, label_message;
    Gtk::Button button1, button2;
    Gtk::HBox hbox1, hbox2, hbox3, hbox4, hbox5, hbox_button;
    Gtk::VBox vbox1;
    virtual std::string vGetCurPass();
	virtual std::string vGetNewPass();
    void on_join_click();
    void on_exit_click() {hide();};
    // MysqlMember *member;
    
public:
    JoinPopup();
};

class ChangeAccount : public JoinPopup
{
protected:
    Gtk::Entry entry6;
    Gtk::Label label6;
    Gtk::HBox hbox6;
    virtual std::string vGetCurPass();
	virtual std::string vGetNewPass();

public:
    ChangeAccount(std::string, std::string, std::string);
};
