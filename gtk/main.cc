#include <gtkmm.h>
#include "win.h"
#include "interface.h"
Interface* pInterface;

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "");
	Win win;
	pInterface = &win;
    return app->run(win);
}


