#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string>
#include <mutex>
#include "Buffer.h"
#include "Socket.h"

#define MAX_STRING_SIZE 200

#define CREATE_GAME_ACTION 0
#define JOIN_GAME_ACTION 1

#define MOVING_OBJECT 0
#define DEAD_OBJECT 1
#define ACTION 2


#define START_TURN 3
#define END_TURN 4
#define MOVE_ACTION 5
#define CHANGE_WEAPON_ACTION 6
#define SHOOT_WEAPON 7
#define SHOOT_SELF_DIRECTED 8

#define MOVE_RIGHT 1
#define MOVE_LEFT -1
#define JUMP 2
#define ROLLBACK 3

#define WORM_TYPE 0
#define WEAPON_TYPE 1
#define GIRDER_TYPE 2

class Protocol {
	private:
		Socket socket;
		std::mutex mutex_send;
	public:
		Protocol(Socket&& socket);
		Protocol(Protocol&& other);
		~Protocol();
		
		void send_buffer(Buffer& buffer);
		Buffer receive_buffer();
		
		void send_int_buffer(Buffer& buffer, int32_t value);
		int receive_int_buffer(Buffer& buffer);
		
		void send_string_buffer(Buffer& buffer, const std::string &string);
		std::string receive_string_buffer(Buffer& buffer);

		void send_length(uint32_t length);
		size_t receive_length();
		
		void stop();

		//Envia un char
		void send_char(unsigned char c);

		//Recibe un char
		unsigned char receive_char();

		//Envia un string
		void send_string(const std::string& string);

		//Recibe un string
		std::string receive_string();
};

#endif
