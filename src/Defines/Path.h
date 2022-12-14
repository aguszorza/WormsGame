#ifndef __PATH_H__
#define __PATH_H__

#include <string>

#ifndef ROOT_PATH
#define ROOT_PATH "."
#endif

const std::string YAML_EXTENSION(".yaml");


//general

const std::string RESOURCES(std::string(ROOT_PATH) + "/resources/");

const std::string IMAGES_PATH(RESOURCES + "Images/");

const std::string MENU_PATH(IMAGES_PATH + "Menu/");

const std::string SOUNDS_PATH(RESOURCES + "Sounds/");

const std::string GLADE_PATH(RESOURCES + "Glade/");

const std::string BACKGROUND_PATH(RESOURCES + "Background/");

const std::string ANIMATIONS_PATH(IMAGES_PATH + "Animations/");

const std::string CONFIG_PATH(std::string(ROOT_PATH) + "/config/");

const std::string MAPS_PATH(std::string(CONFIG_PATH) + "Maps/");

const std::string CLIENT_WINDOW_NAME("Worms");

const std::string EDITOR_WINDOW_NAME("Worms - Editor");

const std::string ICON_PATH(IMAGES_PATH + "icon.png");

//client

const std::string GIRDER_PATH(IMAGES_PATH + "Girder/girder_");

const std::string BULLETS_PATH(IMAGES_PATH + "Bullets/");

const std::string WORMS_PATH(IMAGES_PATH + "Worms/");

const std::string WEAPONS_PATH(IMAGES_PATH + "Weapons_icons/");

const std::string SCOPE_IMAGE(IMAGES_PATH + "Scope/Scope.gif");

const std::string VICTORY_ANIMATION(ANIMATIONS_PATH + "Victory.gif");

const std::string EXPLOSION_ANIMATION(ANIMATIONS_PATH + "Explosion.png");

const std::string TITLE_MENU_IMAGE(MENU_PATH + "Game_title.png");

const std::string BACKGROUND_MENU_IMAGE(MENU_PATH + "Background_worm.png");

const std::string WAITING_ROOM_IMAGE(MENU_PATH + "Waiting_room.png");

const std::string BAT_HIT_ANIMATION(ANIMATIONS_PATH + "Bat_hit.png");

const std::string WINNER_IMAGE(MENU_PATH + "Winner.png");

const std::string LOSER_IMAGE(MENU_PATH + "Loser.png");

const std::string TIE_IMAGE(MENU_PATH + "Tie.png");

const std::string WARNING_IMAGE(MENU_PATH + "Warning.png");

//server

const std::string SERVER_CONFIG_FILE(CONFIG_PATH + "server_config.yaml");

#endif
