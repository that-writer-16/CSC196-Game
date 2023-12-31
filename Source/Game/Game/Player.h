#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, const kiko::Transform transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model }, m_speed{ speed }, m_turnRate{ turnRate }{}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

	float GetHealth() { return m_health; }
private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 1000;
	int m_bombCounter = 5;
};