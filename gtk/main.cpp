#include <gtkmm.h>
#include "win.h"

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "");
	Win win;
    return app->run(win);
}


