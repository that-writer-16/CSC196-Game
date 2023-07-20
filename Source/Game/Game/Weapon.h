#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>
//make weapon in charge of sound
class Weapon : public kiko::Actor
{
public:
	Weapon(float speed, const kiko::Transform transform, std::shared_ptr<kiko::Model> model) ://lifespan parameter?
		Actor{ transform, model }, m_speed{ speed } 
	{
		m_lifespan = 2.0f;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
};