#include "helloworld.h"
#include <iostream>

HelloWorld::HelloWorld()
: m_button("Hello World")   // creates a new button with label "Hello World".
{
  // Sets the border width of the window.
  set_border_width(10);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this, &HelloWorld::on_button_clicked));

  // This packs the button into the Window (a container).
  add(swin);
  swin.add(m_button);
swin.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);
  // The final step is to display this newly created widget...
  //swin.show();
  //m_button.show();
  show_all_children();
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}
