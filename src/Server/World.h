#ifndef __WORLD_H__
#define __WORLD_H__

#include "Thread.h"
#include "b2World.h"
#include "b2Body.h"
#include "PhysicalObject.h"
#include "CollisionListener.h"
#include <mutex>
#include <list>

class World: public Thread{
	private:
		b2World world;
		std::mutex mutex;
		CollisionListener collision_listener;
		std::list<physical_object_ptr> objects;
		std::list<physical_object_ptr> girders;
		std::list<physical_object_ptr> fragments_to_add;
		bool is_active;

		void initialize();
		void removeObject(physical_object_ptr object);

	public:
		World(const b2Vec2& gravity = b2Vec2(0.0f, -10.0));
		~World();

		void run() override;

		void addObject(physical_object_ptr object, const b2Vec2& pos);

		void addWeaponFragment(physical_object_ptr fragment);

		b2Vec2 getObjectPosition(PhysicalObject& object);

		void setLinearVelocity(PhysicalObject& object, b2Vec2& velocity);

		bool isActive();

		b2Body* getClosestObject(b2Vec2 center, b2Vec2 end, b2Vec2& normal);

		std::list<physical_object_ptr>& getObjectsList();

		std::mutex& getMutex();

};


#endif
