#pragma once
#include <random>

namespace kiko
{
	void seedRandom(unsigned int seed) { srand(seed); }
	int random() { return rand(); }
	int random(unsigned int max) { return rand() % max; } // 0 - (max)
	int random(unsigned int min, unsigned int max) { return min + random((max - min) + 1); } // min - max //validate that the min is less than the max
}