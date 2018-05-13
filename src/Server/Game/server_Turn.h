#ifndef __SERVERTURN_H__
#define __SERVERTURN_H__

#include "server_Player.h"
#include <vector>

class Turn{
	private:
		std::vector<Player> players;
		size_t current;

		void advanceCurrent();

	public:
		Turn();
		~Turn();

		void addPlayer(Player&& player);

		size_t get_players_size() const;

		std::vector<Player>& getPlayers();

		Player& getCurrentPlayer();

		void begin_turn();

		void addWorm(World& world, GameParameters& parameters, b2Vec2 position, int id);

		void distributeWorms(size_t size, int life_to_add);

		bool gameEnded();

};

#endif
