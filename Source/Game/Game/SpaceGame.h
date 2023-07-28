#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class SpaceGame : public kiko::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	}; 
public:
	virtual bool Initalize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }
private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 4;
	float m_healthSpawn = 1;
	float m_bombSpawn = 2;
	float m_stateTimer = 0;

	std::shared_ptr<kiko::Font> m_font;
	std::unique_ptr<kiko::Text> m_titleText; // Game Title
	std::unique_ptr<kiko::Text> m_instructionsText;// "Press the space bar to start."
	std::unique_ptr<kiko::Text> m_instructions2Text;// "Press escape to exit."
	std::unique_ptr<kiko::Text> m_healthText; // Player Health
	std::unique_ptr<kiko::Text> m_scoreText; // Player Score
	std::unique_ptr<kiko::Text> m_livesText; // "You have [Player Lives] left."
	std::unique_ptr<kiko::Text> m_gameOverText; // "Game Over"

};