#ifndef __CLIENTPLAYER_H__
#define __CLIENTPLAYER_H__

#include "client_Protocol.h"
#include "WorldView.h"
#include "client_Turn.h"
////////////////////////////////////////////?FALTA IMPLEMENTAR

class Player{
	private:
		Protocol& protocol;
		WorldView& world;
		Turn* turn;

	public:
		Player(Protocol& protocol, WorldView& world);
		~Player();

		void startTurn(int id);
		void endTurn();
		
		bool complete_handler(GdkEventKey* key_event);
		
		Gtk::ScrolledWindow& getWindow();
};

#endif
