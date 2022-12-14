#ifndef __GAMESLIST_H__
#define __GAMESLIST_H__

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <mutex>
#include "Game.h"

typedef std::vector<std::string> games_list_t;

class Server;

class GamesList{
	private:
		Server& server;
		std::unordered_map<std::string, std::unique_ptr<Game>> games;
		std::mutex mutex;
		std::mutex& mutex_cout;

		typedef const std::string string;

	public:
        /* Constructor */
		GamesList(Server& server, std::mutex& mutex_cout);

		/* Destructor */
		~GamesList();

		/* Agrega una patida nueva a la lista */
		bool addGame(string& game_name, string& map, int max_players, Player& player);

		/* Devuelve una lista con las partidas a las cuales se puede
		 * unir el jugador */
		games_list_t getJoinableGames(const std::string& player_name);

		/* Agrega un jugador a la partida */
		bool addPlayer(const std::string& game_name, Player& player);

		/* Verifica las partidas que terminaron */
		void checkGames();
};

#endif
