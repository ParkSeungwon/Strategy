#include <string>
#include "teamsetup.h"
using namespace std;

const char *Nations[] = {"Americans", "Australians", "British", "Canadians",
	"Chinese", "French", "Germans", "Italians", "Japanese", "Neutral", 
	"Puppet_States", "Russians"};
const char *Type[] = {"User", "Human", "CPU"};
map<string, int> Teams;

TeamSetup::TeamSetup(int c)
{
	set_title("Team setup");
	Gtk::Box *box = get_content_area();
	hboxes = new Gtk::HBox[c];
	comboboxes = new Gtk::ComboBoxText[c * 3];
	string s;
	for(int i=0; i<c; i++) {
		box->pack_start(hboxes[i]);
		hboxes[i].pack_start(comboboxes[i]);
		hboxes[i].pack_start(comboboxes[i + c]);
		hboxes[i].pack_start(comboboxes[i + c + c]);
		comboboxes[i].append("User");
		comboboxes[i].append("Human");
		comboboxes[i].append("CPU");
		for(int j=0; j<12; j++) comboboxes[i +c].append(Nations[j]);
		for(int j=1; j<=c; j++) {
			s = "Team" + to_string(j);
			comboboxes[i + c + c].append(s);
		}
		comboboxes[i].set_active(2);
		comboboxes[i + c].set_active(i);
		comboboxes[i + c + c].set_active(i);
	}
	comboboxes[0].set_active(0);
	add_button("_Start game", 1);
	add_button("cancel", 2);

	show_all_children();
}

TeamSetup::~TeamSetup()
{
	delete [] comboboxes;
	delete [] hboxes;
}

vector<array<int, 3>> setup(int c)
{
	TeamSetup ts(c);
	vector<array<int, 3>> v;
	array<int, 3> ar;

	int result = ts.run();
	if(result == 1) {
		for(int i=0; i<c; i++) {
			ar[0] = ts.comboboxes[i].get_active_row_number();
			ar[1] = ts.comboboxes[i+c].get_active_row_number();
			ar[2] = ts.comboboxes[i+c+c].get_active_row_number();
			v.push_back(ar);
		}
	}
	return v;
}
