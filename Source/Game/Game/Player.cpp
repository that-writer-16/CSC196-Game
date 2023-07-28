#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/ModelManager.h"
#include "Framework/Emitter.h"
#include "Audio/AudioSystem.h"
#include <iostream>

void Player::Update(float dt)
{
	kiko::g_audioSystem.AddAudio("bullet", "shoot.wav");
	kiko::g_audioSystem.AddAudio("bomb", "explosion.wav");
	kiko::g_audioSystem.AddAudio("hurt", "hurt.wav");
	kiko::g_audioSystem.AddAudio("power", "powerup.wav");
	//movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	AddForce(forward * m_speed * thrust);
	m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	//fire weapon left
	if (kiko::g_inputSystem.GetMouseButtonDown(0))
	{
		kiko::Transform transform{ m_transform.position, m_transform.rotation, 1 };
		std::unique_ptr<Weapon> bullet = std::make_unique<Weapon>(400.0f, transform, kiko::g_manager.Get("bullet.txt"));
		kiko::g_audioSystem.PlayOneShot("bullet", false);
		bullet->m_tag = "Bullet";
		m_scene->Add(std::move(bullet));
	}
	//fire weapon right
	if (kiko::g_inputSystem.GetMouseButtonDown(2) && 
		kiko::g_inputSystem.GetMousePreviousButtonDown(2) 
		&& m_bombCounter != 0)
	{
		m_bombCounter -= 1;
		kiko::Transform transform{ m_transform.position, m_transform.rotation, 1 };
		std::unique_ptr<Weapon> bomb = std::make_unique<Weapon>(400.0f, transform, kiko::g_manager.Get("bomb.txt"));
		kiko::g_audioSystem.PlayOneShot("bomb", false);
		bomb->m_tag = "Bomb";
		m_scene->Add(std::move(bomb));
	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(4);
	else kiko::g_time.SetTimeScale(1);
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "Health")
	{
		kiko::g_audioSystem.PlayOneShot("power", false);
		m_health = 1000;
	}
	if (other->m_tag == "More Bombs") 
	{
		kiko::g_audioSystem.PlayOneShot("power", false);
		m_bombCounter = 5;
	}
	if (other->m_tag == "Enemy Weapon")
	{
		kiko::g_audioSystem.PlayOneShot("bomb", false);
		m_health -= 50.0f;
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
			emitter->SetLifespan(2.0f);
			emitter->Draw(kiko::g_renderer);
			m_scene->Add(std::move(emitter));

			m_game->SetLives(m_game->GetLives() - 1);
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
			m_destroyed = true;
		}
	}
}
