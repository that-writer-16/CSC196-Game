#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Health.h"
#include "Bomb.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"
#include "Renderer/ParticleSystem.h"
#include "Framework/Scene.h"

bool SpaceGame::Initalize()
{
	m_font = std::make_shared<kiko::Font>("2015 Cruiser.ttf", 24);

	
	m_livesText = std::make_unique<kiko::Text>(m_font);
	m_gameOverText = std::make_unique<kiko::Text>(m_font);
	m_scoreText = std::make_unique<kiko::Text>(m_font);
	
	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "StarField", kiko::Color{ 1, 1, 1, 1 });	
	
	m_healthText = std::make_unique<kiko::Text>(m_font);
	
	m_instructionsText = std::make_unique<kiko::Text>(m_font);
	m_instructions2Text = std::make_unique<kiko::Text>(m_font);
	m_instructionsText->Create(kiko::g_renderer, "Press Spacebar to start.", kiko::Color{ 1, 1, 1, 1 });
	m_instructions2Text->Create(kiko::g_renderer, "Press Escape to exit.", kiko::Color{ 1, 1, 1, 1 });

	kiko::g_audioSystem.AddAudio("select", "select.wav");

	m_scene = std::make_unique<kiko::Scene>();

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::g_audioSystem.PlayOneShot("select", false);

			m_state = eState::StartGame;
		}
		break;
	case SpaceGame::eState::StartGame:
		
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		std::unique_ptr<Player> player = std::make_unique<Player>(150.0f, kiko::Pi, kiko::Transform{ { 400, 300}, 0, 6 }, kiko::g_manager.Get("ship.txt"));
		player->m_tag = "Player"; //could put it in the constructor
		player->SetDamping(0.1f);
		player->m_game = this;
		m_scene->Add(std::move(player));
	}
		m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		m_healthSpawn += dt;
		m_bombSpawn += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(100, 181), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(400)}, kiko::randomf(kiko::TwoPi), 2}, kiko::g_manager.Get("rocket.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
			m_spawnTimer = 0;
			
		}
		if (m_healthSpawn >= m_spawnTime)
		{
			std::unique_ptr<Health> health = std::make_unique<Health>(kiko::Transform{ { kiko::random(800), kiko::random(400)}, kiko::randomf(kiko::TwoPi), 2}, kiko::g_manager.Get("health.txt"));
			health->m_tag = "Health";
			health->m_game = this;
			m_scene->Add(std::move(health));
			m_healthSpawn = 0;
		}		
		if (m_bombSpawn >= m_spawnTime)
		{
			std::unique_ptr<Bomb> bomb = std::make_unique<Bomb>(kiko::Transform{ { kiko::random(800), kiko::random(400)}, kiko::randomf(kiko::TwoPi), 2}, kiko::g_manager.Get("bomb.txt"));
			bomb->m_tag = "More Bombs";
			bomb->m_game = this;
			m_scene->Add(std::move(bomb));
			m_bombSpawn = 0;
		}
		break;
	case SpaceGame::eState::PlayerDeadStart:
		m_stateTimer = 3;
		m_state = eState::PlayerDead;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;

		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		m_livesText->Create(kiko::g_renderer, "Lives left: " + std::to_string(m_lives), { 1, 1, 1, 1 });
		if (m_stateTimer <= 0)
		{
			if (m_lives == 0) m_state = eState::GameOver;
			else
			{
				m_state = eState::StartLevel;
			}
		}
		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
			m_gameOverText->Create(kiko::g_renderer, "Game Over", { 1, 1, 1, 1 });
		if (m_stateTimer <= 0)
		{
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(kiko::g_renderer, "Score " + std::to_string(m_score), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 200, 300);
		m_instructionsText->Draw(renderer, 200, 400);
		m_instructions2Text->Draw(renderer, 200, 450);
	}
	if (m_state == eState::Game)
	{
		m_healthText->Create(kiko::g_renderer, "Health " + std::to_string((int)m_scene->GetActor<Player>()->GetHealth()), {1, 1, 1, 1});
		m_healthText->Draw(renderer, 100, 100);
		m_scoreText->Draw(renderer, 500, 500);
	}
	if (m_state == eState::PlayerDead) {
		m_livesText->Draw(renderer, 300, 300);
	}
	if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 500, 500);
		m_scoreText->Draw(renderer, 300, 300);
	}
	m_scene->Draw(renderer);
}
