#include "Enemy.h"
#include "Player.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Weapon.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + kiko::HalfPi;
	}

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	//fireRate is when to show up. firetimer is it actaually showing up. 
	//make enemies fire weapons

	//fire weapon
	kiko::Transform transform{ m_transform.position, m_transform.rotation, 1 };
	std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
	weapon->m_tag = "EnemyWeapon";
	m_scene->Add(std::move(weapon));

	//bool done = false;
	//int	timer = 0;
	//while (!done)
	//{
	//	timer++;
	//	if (m_fireTimer == m_fireRate)
	//	{
	//		kiko::Transform transform{ m_transform.position, m_transform.rotation, 1 };
	//		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
	//		m_scene->Add(std::move(weapon));
	//		m_fireTimer--;

	//		if (m_fireTimer == 0) m_fireTimer = m_fireRate;
	//	}
	//	if (timer == 15) done = true;
	//}
}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag == "Player")
	{
		m_health -= 1.5f;
		if (m_health <= 0)
		{
			m_destroyed = true;
		}
	}
}
