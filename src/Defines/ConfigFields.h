#ifndef __CONFIGFIELDS_H__
#define __CONFIGFIELDS_H__

#include <string>

//config del server

const std::string SERVER_PORT("port");

const std::string DATA_SENDER_SLEEP("data_sender_sleep");

const std::string GAME_WAIT_WORLD_SLEEP("game_waiting_world_sleep");

const std::string WORLD_SLEEP_AFTER_STEP("world_sleep_after_step");

const std::string WORLD_TIME_STEP("world_time_step");

const std::string TURN_TIME("turn_time");

const std::string TIME_AFTER_SHOOT("time_after_shoot");

const std::string WORMS_LIFE_TO_ADD("worms_life_to_add");

const std::string WORM_VELOCITY("worm_velocity");

const std::string WORM_EXPLOSION_VELOCITY("worm_explosion_velocity");

const std::string WORM_JUMP_VELOCITY("worm_jump_velocity");

const std::string WORM_ROLLBACK_VELOCITY("worm_rollback_velocity");

const std::string WORM_JUMP_HEIGHT("worm_jump_height");

const std::string WORM_ROLLBACK_HEIGHT("worm_rollback_height");

const std::string WEAPONS_VELOCITY("weapons_velocity");

const std::string WEAPON_DAMAGE("weapon_damage");

const std::string WEAPON_RADIUS("weapon_radius");

const std::string WEAPON_FRAGMENTS("weapon_fragments");

const std::string WIND_MIN_VELOCITY("wind_min_velocity");

const std::string WIND_MAX_VELOCITY("wind_max_velocity");

const std::string GRAVITY("gravity");

const std::string AIR_MISSILES_SEPARATION("air_missiles_separation");

const std::string WORM_HEIGHT_TO_DAMAGE("worm_height_to_damage");

const std::string WORM_MAX_HEIGHT_DAMAGE("worm_max_height_damage");

const std::string GIRDER_ANGLE_FRICTION("max_girder_rotation_friction");

const std::string WORLD_MAX_HEIGHT("world_max_height");

//config del editor

const std::string BACKGROUND_IMAGE("background_image");

const std::string WORMS_LIFE("worms_life");

const std::string WORMS_DATA("worms");

const std::string GIRDERS_DATA("girders");

const std::string WEAPON_AMMO("weapon_ammo");

#endif
