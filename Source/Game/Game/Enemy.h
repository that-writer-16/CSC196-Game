#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>

class Enemy : public kiko::Actor
{
public:
	Enemy(float speed, float turnRate, const kiko::Transform transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model }, m_speed{ speed }, m_turnRate{ turnRate } 
	{
		m_fireRate = 10.0f;
		m_fireTimer = m_fireRate;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;


private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 25;
	float m_fireTimer = 0;
	float m_health = 100;
	float m_lifespan;

};