#include <gtkmm.h>
#include "win.h"
#include"Time.h"
int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "");
	Time time;
	Win win;
    return app->run(win);
}


