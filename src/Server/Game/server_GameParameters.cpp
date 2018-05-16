#include "GameParameters.h"
#include <algorithm>
#include <random>

GameParameters::GameParameters(const std::string& config_file, const std::string& config_editor):
	config(YAML::LoadFile(config_file)), config_editor(YAML::LoadFile(config_editor)){}
	
GameParameters::~GameParameters(){}

int GameParameters::getWormLife(){
	return this->config_editor["worms_life"].as<int>();
}

int GameParameters::get_worms_life_to_add(){
	return this->config["worms_life_to_add"].as<int>();
}

std::vector<b2Vec2> GameParameters::getWorms(){
	std::vector<b2Vec2> worms;
	std::vector<std::vector<int>> worms_file = config_editor["worms"].as<std::vector<std::vector<int>>>();

	for (auto it = worms_file.begin(); it != worms_file.end(); ++it){
		worms.push_back(b2Vec2((*it)[0], (*it)[1]));
	}

	std::random_device rd;
    std::mt19937 random(rd());
 
    //std::shuffle(worms.begin(), worms.end(), random);////////////////////////////////////////para probar cosas saco el random
	return worms;
}

std::vector<GirderParams> GameParameters::getGirders(){
	std::vector<GirderParams> girders;
	std::vector<std::vector<int>> girders_file = config_editor["girders"].as<std::vector<std::vector<int>>>();

	for (auto it = girders_file.begin(); it != girders_file.end(); ++it){
		girders.push_back(GirderParams((*it)[0], (*it)[1], (*it)[2], (*it)[3]));
	}
	return girders;
}

std::map<std::string, int> GameParameters::getWeaponsAmmo(){
	std::map<std::string, int> ammo = config_editor["weapon_ammo"].as<std::map<std::string, int>>();
	return ammo;
}

float GameParameters::getWormVelocity(){
	return this->config["worm_velocity"].as<float>();
}

float GameParameters::getWormJumpVelocity(){
	return this->config["worm_jump_velocity"].as<float>();
}

float GameParameters::getWormRollbackVelocity(){
	return this->config["worm_rollback_velocity"].as<float>();
}

float GameParameters::getWormJumpHeight(){
	return this->config["worm_jump_height"].as<float>();
}

float GameParameters::getWormRollbackHeight(){
	return this->config["worm_rollback_height"].as<float>();
}

float GameParameters::getWeaponsVelocity(){
	return this->config["weapons_velocity"].as<float>();
}

int GameParameters::getWeaponDamage(const std::string& weapon){
	return this->config["weapon_damage"][weapon].as<int>();
}

int GameParameters::getWeaponRadius(const std::string& weapon){
	return this->config["weapon_radius"][weapon].as<int>();
}

int GameParameters::getWeaponFragments(const std::string& weapon){
	return this->config["weapon_fragments"][weapon].as<int>();
}

GameParameters::GirderParams::GirderParams(size_t len, int pos_x, int pos_y, int rotation):
	len(len), pos_x(pos_x), pos_y(pos_y), rotation(rotation){}
