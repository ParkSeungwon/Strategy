#include <string>
#include <iostream>
#include "main.h"
using namespace Gtk;
using namespace std;

Win::Win() :
   	bt1("OK"), bt2("cancel"), box2(ORIENTATION_VERTICAL), bt3("open"), label1("라벨") 
{
    set_border_width(10);
    set_default_size(900, 900);
    add(box1);
    swin.add(area);
    swin.set_policy(Gtk::POLICY_ALWAYS, POLICY_ALWAYS);
	box1.pack_start(box2, PACK_SHRINK);
	box1.pack_start(swin);
    box2.pack_start(bt1, PACK_SHRINK);
    box2.pack_start(bt2, PACK_SHRINK);
    box2.pack_start(bt3, PACK_SHRINK);
	box2.pack_start(label1, PACK_SHRINK);
 //   cout << "높이 " << area.height << endl;
 //   area.set_size_request(area.width, area.height);
    box1.pack_start(area);
    bt1.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_button_click));
    bt2.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_cancel_click));
    bt3.signal_clicked().connect(sigc::mem_fun(*this, &Win::on_open_click));
    show_all_children();
}

bool Win::on_button_press_event(GdkEventButton* e)
{
	label_change(e->x, e->y, e->button);
}

bool Win::on_key_press_event(GdkEventKey* e)
{
	cout << "key : " << e->keyval << endl;
	label1.set_text(to_string(e->keyval));
	return false;
}

int Win::label_change(int x, int y, int bt)
{
	string s;
	s = to_string(x);
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
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog.add_filter(filter_any);
	//Show the dialog and wait for a user response:
	int result = dialog.run();

	//Handle the response:
	switch(result) {
    case(Gtk::RESPONSE_OK):
    {
		std::cout << "Open clicked." << std::endl;

		//Notice that this is a std::string, not a Glib::ustring.
		std::string filename = dialog.get_filename();
		std::cout << "File selected: " <<  filename << std::endl;
		area.open_map_file(filename);
		break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}
void Win::on_button_click()
{
	area.clear_map();
	area.paste_pix(100 + i_++, 1900, "units/Americans/bomber_hb.png", 1 + f_++);
	area.paste_pix(500, 1900, "units/Chinese/battlecruiser.png", M_PI);
    // force our program to redraw the entire clock.
	area.refresh();
}


void Win::on_cancel_click()
{
	area.insert_to_draw(300 + i_++*10, 300, 100, 100, 0, M_PI/2, 
				(i_%10)/10.0, 0.4, 0.0, 0.2);
	area.refresh();
}

int main(int argc, char** argv)
{
    auto app = Application::create(argc, argv, "");

    Win win;
    return app->run(win);
}


