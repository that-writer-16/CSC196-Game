#include "Bomb.h"

void Bomb::Update(float dt)
{
	Actor::Update(dt);
}

void Bomb::OnCollision(Actor* other)
{
	if (other->m_tag == "Player")
	{
		m_destroyed = true;
	}
}
