#pragma once
#include "Framework/Actor.h"
//make weapon in charge of sound
class Weapon : public kiko::Actor
{
public:
	Weapon(float speed, const kiko::Transform transform, kiko::Model model) :
		Actor{ transform, model }, m_speed{ speed } {}
	void Update(float dt) override;

private:
	float m_speed = 0;
};