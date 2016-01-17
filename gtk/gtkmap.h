class GtkMap : public Gtk::DrawingArea
{
	public:
		GtkMap(){}
//		virtual ~MainWindow ();

	protected:
		virtual bool on_expose_event(GdkEventExpose* event);
	private:
		/* data */
};
