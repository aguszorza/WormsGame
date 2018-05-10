#ifndef __WORM_H__
#define __WORM_H__

#include "PhysicalObject.h"
#include "GameParameters.h"

class Worm: public PhysicalObject{	
	private:
		int life;
		char dir;
		GameParameters& parameters;


	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		Worm(World& world, int id, GameParameters& parameters);
		~Worm();

		int getLife();
		char getDir();

		void move(char action);

		void changeWeapon(const std::string& weapon);

		void shoot(int angle, int power, int time);

		void shoot(b2Vec2 pos);

		void collide_with_something(CollisionData* other) override;
};

typedef std::shared_ptr<Worm> worm_ptr;

#endif