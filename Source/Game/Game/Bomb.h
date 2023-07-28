#pragma once
#include "Framework/Actor.h"
#include <Renderer/Model.h>

class Bomb : public kiko::Actor
{
public:
	Bomb(const kiko::Transform transform, std::shared_ptr<kiko::Model> model) :
		Actor{ transform, model } {}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_lifespan = 1;
};