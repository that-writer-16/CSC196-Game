#pragma once
#include "Core/Core.h"
#include "Render.h"
#include <vector>

namespace kiko
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		void Draw(Renderer renderer);
	private:
		std::vector<vec2> m_points;
	};
}