
#include <glibmm/refptr.h>

#include "WeaponListt.h"

WeaponListt::WeaponListt(const Glib::RefPtr<Gtk::Builder> &builder) {
    for (size_t i = 1; i <= 10; ++i) {
        std::shared_ptr<WeaponView> weapon_view(new WeaponView(builder, i));

        std::shared_ptr<WeaponModel> weapon
                (new WeaponModel(weapon_view->getInitialAmmo()));

        weapons.push_back(weapon);

        std::shared_ptr<WeaponController> weapon_controller(
                new WeaponController(weapon_view,
                                     weapon));
        wep_controllers.push_back(std::move(weapon_controller));
        weapons_view.push_back(weapon_view);
    }
}

void WeaponListt::reset_ammo() {
    for (const std::shared_ptr<WeaponController> &actual_controller:wep_controllers) {
        actual_controller->reset_ammo();
    }
}