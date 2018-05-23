
#include "editor_WeaponModel.h"

WeaponModel::WeaponModel(const int & default_ammo)
        : default_ammo(default_ammo),
          actual_ammo(default_ammo) {}

void WeaponModel::reset_ammo() {
    actual_ammo = default_ammo;
}

void WeaponModel::set_ammo(const int &new_ammo) {
    this->actual_ammo = new_ammo;
}
