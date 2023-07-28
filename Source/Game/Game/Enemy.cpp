#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->m_transform.position - m_transform.position;

		float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());

		m_transform.rotation += turnAngle * dt;

		if (std::fabs(turnAngle) < kiko::DegToRad(30.0f))
		{
			//I see you. SO Shoot
				//fire weapon
			m_fireTimer += kiko::g_time.GetDeltaTime();
			if (m_fireTimer >= m_fireRate)
			{
				kiko::Transform transform{ m_transform.position, m_transform.rotation, 1 };
				std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
				weapon->m_tag = "Enemy Weapon";
				m_scene->Add(std::move(weapon));
				m_fireTimer = 0;
			}
		}
	}

	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());
}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag == "Health")
	{
		m_health = 100;
	}
	if (other->m_tag == "Bullet")
	{
		m_health -= 10.0f;
		m_game->AddPoints(1);
		if (m_health <= 0)
		{
			kiko::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = kiko::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMax = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = kiko::Color{ 1, 1, 1, 1 };

			auto emitter = std::make_unique<kiko::Emitter>(m_transform, data);
			emitter->SetLifespan(1.0f);
			emitter->Draw(kiko::g_renderer);
			m_scene->Add(std::move(emitter));

			m_game->AddPoints(20);
			m_destroyed = true;
		}
	}
	if (other->m_tag == "Bomb")
	{
		m_health -= 100.0f;
		m_game->AddPoints(5);
		if (m_health <= 0)
		{
			kiko::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = kiko::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMax = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = kiko::Color{ 0, 1, 0, 1 };

			auto emitter = std::make_unique<kiko::Emitter>(m_transform, data);
			emitter->SetLifespan(3.0f);
			emitter->Draw(kiko::g_renderer);
			m_scene->Add(std::move(emitter));

			m_game->AddPoints(20);
			m_destroyed = true;
		}
	}
}
