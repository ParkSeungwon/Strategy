#include "myarea.h"
#include <gtkmm.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  Gtk::Window win;
  win.set_title("DrawingArea");
  win.set_default_size(300, 200);

  MyArea area;
//  Gtk::ScrolledWindow swin;
// Gtk::Viewport v;
//  swin.add(area);
  //v.add(area);
  Gtk::Button bt("OK");
  Gtk::Box b;
  //b.pack_start(area);
  //b.pack_start(bt);
  win.add(bt);
//  area.show();
  
  area.set_receives_default();
  //win.show();
//:show_all_children();
//swin.show();
  return app->run(win);
}
