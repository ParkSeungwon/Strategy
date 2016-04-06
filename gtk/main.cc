#include <gtkmm.h>
#include "win.h"
#include "interface.h"
Interface* pInterface;

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "");
//	Time time;
	Win win;
	pInterface = &win;
//	Control control(win.area, time);
    return app->run(win);
}


