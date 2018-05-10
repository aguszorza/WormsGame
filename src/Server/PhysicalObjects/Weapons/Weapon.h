#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "Worm.h"
#include "PhysicalObject.h"
#include "GameParameters.h"
#include <string>

class Weapon: public PhysicalObject{
	protected:
		GameParameters& parameters;
		int damage;
		int radius;
		bool waiting_to_explode;
		int time_to_explode;
		int angle;
		int power;

		void createFixtures() override;
		void setInitialVelocity() override;

	private:
		int ricochets;

	public:
		static int id;

		Weapon(World& world, GameParameters& parameters, int damage, int radius = 0, int ricochets = 0);
		~Weapon();

		virtual void shoot(int angle, int power, int time);

		virtual void shoot(Worm& shooter, b2Vec2 pos);

		virtual void explode();

		virtual void collide_with_something(CollisionData* other) override;

		bool isMoving() override;

		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;

		virtual std::string getName() = 0;

};

#endif