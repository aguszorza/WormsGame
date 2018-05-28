#include "GameMenu.h"
#include <gtkmm/builder.h>
#include "Path.h"

GameMenu::GameMenu(Gtk::Window& window, ClientProtocol&& protocol): window(window), protocol(std::move(protocol)){
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(GLADE_PATH + "client_GameMenu.glade");

	builder->get_widget("error", this->error);
	builder->get_widget("player_name", this->player_name);

	builder->get_widget("game_menu", this->menu);
	this->window.add(*this->menu);
	this->menu->show();


	Gtk::Button *create_game, *join_game;
	builder->get_widget("create_game", create_game);
	builder->get_widget("join_game", join_game);
	create_game->signal_clicked().connect(sigc::mem_fun(*this, &GameMenu::createButtonPressed));
	join_game->signal_clicked().connect(sigc::mem_fun(*this, &GameMenu::joinButtonPressed));
}

GameMenu::~GameMenu(){}

void GameMenu::createButtonPressed(){
	if (this->selectAction(CREATE_GAME_ACTION)){
		std::string name(this->player_name->get_text());
		int quantity = this->protocol.receiveLength();
		if (quantity == 0){
			this->error->set_label("No hay mapas para crear una partida");
			this->showError();
		} else {
			this->create_menu = std::unique_ptr<CreateGameMenu>(new CreateGameMenu(this->window, std::move(this->protocol), std::move(name), quantity));
		}
	}
}

void GameMenu::joinButtonPressed(){
	if (this->selectAction(JOIN_GAME_ACTION)){
		std::string name(this->player_name->get_text());
		int quantity = this->protocol.receiveLength();
		if (quantity == 0){
			this->error->set_label("No hay partidas disponibles");
			this->showError();
		} else {
			this->join_menu = std::unique_ptr<JoinGameMenu>(new JoinGameMenu(this->window, std::move(this->protocol), std::move(name), quantity));
		}
	}
}

bool GameMenu::selectAction(char action){
	std::string name(this->player_name->get_text());
	if (name.empty()){
		this->error->set_label("Debe ingresar su nombre");
		return false;
	}
	try{
		this->protocol.sendChar(action);
		this->protocol.sendString(name);
		this->window.remove();
		return true;
	} catch (const SocketException& e){
		this->error->set_label("Ocurrio un error");
		this->showError();
		return false;
	}
}

void GameMenu::showError(){
	this->menu->remove(*this->error);
	this->window.remove();
	this->window.add(*this->error);
}
