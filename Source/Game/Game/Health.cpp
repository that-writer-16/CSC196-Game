#include "Health.h"

void Health::Update(float dt)
{
	Actor::Update(dt);
}

void Health::OnCollision(Actor* other)
{
	if (other->m_tag == "Player")
	{
		m_destroyed = true;
	}
	if (other->m_tag == "Enemy")
	{
		m_destroyed = true;
	}
}
