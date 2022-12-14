#include "Banana.h"
#include "b2Fixture.h"
#include "b2CircleShape.h"
#include <string>

Banana::Banana(World& world, GameParameters& parameters):
	Weapon(world, parameters,
		parameters.getWeaponDamage(BANANA_NAME),
		parameters.getWeaponRadius(BANANA_NAME)){}
		
Banana::~Banana(){}

const std::string& Banana::getName(){
	return BANANA_NAME;
}

void Banana::createFixtures(){
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = weapon_size / 2; 
		  
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 4;
	fixtureDef.restitution = 0.9; //rebotable
	this->body->CreateFixture(&fixtureDef);
}
