#include "darea.h"

Darea::Darea()
{
	DIR* dir;
	
}

Darea::load_map(string file)
{
	map = Gdk::Pixbuf::create_from_file(file);
	Cairo::set_source_pixbuf(*context, map, 0, 0);
}

