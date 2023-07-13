#include "Model.h"
#include "Core/Vector2.h"
#include <sstream>

bool kiko::Model::Load(const std::string& filename)
{
	std::string buffer;
	kiko::readFile(filename, buffer);

	std::istringstream stream(buffer);
	std::string line;
	std::getline(stream, line);

	int numPoints = std::stoi(line);
	for (int i = 0; i < numPoints; i++)
	{
		vec2 point;
		stream >> point;

		m_points.push_back(point);
	}

	return true;
}

void kiko::Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
{
for (int i = 0; i < (m_points.size() - 1); i++)
	{
		if (m_points.empty()) return;
		vec2 p1 = (m_points[i] * scale).Rotate(rotation) + position;
		vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + position;

		renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}