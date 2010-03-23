#include "gspot.h"

using namespace Gtk;

CMainWin::CMainWin()
{
	_win.set_title("GSpot");
	_win.set_border_width(0);

	VBox mainbox(false, 0);
	HBox centerbox(false, 0);
	HBox searchbox(false, 0);
	VBox leftbox(false, 0);
	VBox rightbox(false, 0);

	Entry searchfield;

	ListViewText playlists(1, false, SELECTION_SINGLE);
	playlists.set_column_title(0, "");
	playlists.append_text("Home");

	ListViewText tracks(5, false, SELECTION_SINGLE);
	tracks.set_column_title(0, ""); // Play Icon
	tracks.set_column_title(1, "Track");
	tracks.set_column_title(2, "Artist");
	tracks.set_column_title(3, "Time");
	tracks.set_column_title(4, "Album");

	searchbox.add(searchfield);
	leftbox.add(playlists);
	rightbox.add(tracks);

	centerbox.add(leftbox);
	centerbox.add(rightbox);

	mainbox.add(searchbox);
	mainbox.add(centerbox);

	_win.add(mainbox);
	_win.show_all();

	Gtk::Main::run(_win);
}

CMainWin::~CMainWin()
{
}
