#include "Turn.h"
#include <string>
#include <vector>

Turn::Turn(): current(0){}

Turn::~Turn(){
	for (auto it = this->receivers.begin(); it != this->receivers.end(); ++it){
		(*it)->stop();
		(*it)->join();
	}
}

bool Turn::addPlayer(Player& player){
	if (!this->playerCanJoin(player.getName())){
		return false;
	}
	player.setId(this->players.size());
    player.getProtocol().sendChar(true);
	this->players.push_back(std::move(player));
	return true;
}

bool Turn::playerCanJoin(const std::string& player_name){
	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		if (it->getName() == player_name){
			return false;
		}
	}
	return true;
}

size_t Turn::getPlayersSize() const{
	return this->players.size();
}

Player& Turn::getCurrentPlayer(){
	return this->players.at(this->current);
}

void Turn::startGame(DataSender& data_sender){
	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		PlayerDataReceiver* r = new PlayerDataReceiver(*it, data_sender);
		std::unique_ptr<PlayerDataReceiver> receiver(r);
		receiver->start();
		this->receivers.push_back(std::move(receiver));
	}
}

void Turn::beginTurn(){
	do {
		this->advanceCurrent();
	} while (this->getCurrentPlayer().isDead());
	this->getCurrentPlayer().beginTurn();
	this->receivers[this->current]->beginTurn();
}

void Turn::endTurn(){
	this->receivers[this->current]->endTurn();
}

std::vector<Player>& Turn::getPlayers(){
	return this->players;
}

void Turn::advanceCurrent(){
	this->current++;
	if (this->current >= this->players.size()){
		this->current = 0;
	}
}

void Turn::addWorm(World& world, GameParameters& params, b2Vec2 pos, int id){
	this->players[this->current].addWorm(world, params, pos, id);
	this->advanceCurrent();
}

void Turn::distributeWorms(size_t size, int life_to_add){
	int quantity = (size / this->players.size());
	if (size % this->players.size() != 0){
		quantity += 1;
	}

	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		it->distributeWorms(quantity, life_to_add);
	}
}

bool Turn::gameEnded(std::mutex& mutex){
	std::lock_guard<std::mutex> lock(mutex);
	this->winner.clear();
	size_t players_alive = 0;
	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		if (!it->isDead()){
			players_alive++;
			this->winner = it->getName();
		}
	}
	return players_alive <= 1;
}

const std::string& Turn::getWinner(){
	for (auto it = this->receivers.begin(); it != this->receivers.end(); ++it){
		(*it)->stop();
	}
	return this->winner;
}
