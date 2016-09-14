#include<gtkmm.h>
using namespace std;

string choose_map()
{
	Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN);
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
	if(result == Gtk::RESPONSE_OK) return dialog.get_filename();
	else return "exit";
}
