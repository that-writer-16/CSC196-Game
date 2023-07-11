#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
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
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	kiko::InputSystem inputSystem;
	inputSystem.Initialize();

	//std::vector<vec2> points{ { -10, 5 }, { 10, 5 }, { 0, -5 }, { -10, 5 } };
	kiko::Model model;
	model.Load("ship.txt");

	kiko::vec2 v{ 5, 5 };
	v.Nomalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	kiko::vec2 position{ 400, 500 };
	float speed = 50.0f;

	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();
		inputSystem.Update();
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		kiko::vec2 direction;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		position += direction * speed * kiko::g_time.GetDeltaTime();

		if (inputSystem.GetMouseButtonDown(0))
		{
			cout << "Left Button Pressed." << endl;
		}
		else if (inputSystem.GetMouseButtonDown(1))
		{
			cout << "Middle Button Pressed." << endl;
		}
		else if (inputSystem.GetMouseButtonDown(2))
		{
			cout << "Right Button Pressed." << endl;
		}

		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		// draw
		for (auto& star : stars)
		{
			star.Update(renderer.GetWidth(), renderer.GetHeight());

			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			
			star.Draw(renderer);
		}

		model.Draw(renderer, position, 2.75f);
		
		renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100));
	}
	return 0;
}