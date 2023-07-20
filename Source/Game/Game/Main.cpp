#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Scene.h"
#include <iostream>
#include <vector>
#include <thread>

using namespace std;
using vec2 = kiko::Vector2;

class Star
{
public:
	Star(const vec2& pos, const vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;
};

int main(int argc, char* argv[])
{
	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();

	kiko::g_audioSystem.Initialize();
	kiko::g_audioSystem.AddAudio("shoot", "shoot.wav");

	//share models in teams

	kiko::vec2 v{ 5, 5 };
	v.Nomalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	kiko::Scene scene;
	unique_ptr<Player> player = make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ { 400, 300}, 0, 6 }, kiko::g_manager.Get("ship.txt"));
	player-> m_tag = "Player"; //could put it in the constructor
	scene.Add(move(player));
	std::vector<Enemy> enemies;
	for (int i = 0; i < 5; i++)
	{
		unique_ptr<Enemy> enemy = make_unique<Enemy>(kiko::randomf(100, 181), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(400)}, kiko::randomf(kiko::TwoPi), 2}, kiko::g_manager.Get("s.txt"));
		enemy->m_tag = "Enemy";
		scene.Add(move(enemy));
	}

	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		kiko::g_audioSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::g_audioSystem.PlayOneShot("shoot");
		}

		scene.Update(kiko::g_time.GetDeltaTime());
		//Background color
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		// draw
		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());

			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			
			star.Draw(kiko::g_renderer);
		}

		scene.Draw(kiko::g_renderer);
		
		kiko::g_renderer.EndFrame();
	}
	stars.clear();//may or may not have affected bytes allocated
	scene.RemoveAll();

	return 0;
}