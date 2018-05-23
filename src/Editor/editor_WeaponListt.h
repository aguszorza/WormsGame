
#ifndef WORMS_WEAPONLISTT_H
#define WORMS_WEAPONLISTT_H

#include <gtkmm/builder.h>

#include "editor_WeaponController.h"
#include "editor_WeaponModel.h"

class WeaponListt {
    std::vector<std::shared_ptr<WeaponModel>> weapons;
    std::vector<std::shared_ptr<WeaponView >> weapons_view;
    std::vector<std::shared_ptr<WeaponController> > wep_controllers;
public:
    explicit WeaponListt(const Glib::RefPtr<Gtk::Builder> &builder);

    void reset_ammo();
};


#endif //WORMS_WEAPONLISTT_H
