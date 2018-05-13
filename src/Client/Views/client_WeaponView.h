#ifndef __CLIENTWEAPONVIEW_H__
#define __CLIENTWEAPONVIEW_H__

#include <gtkmm/grid.h>
#include "client_WeaponList.h"

class WeaponView {
	private:
		WeaponList& weapons;
		Gtk::Grid window;

	public:
		WeaponView(WeaponList& weapons);
		~WeaponView();
};

#endif
