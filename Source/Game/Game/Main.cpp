#include "Core/Random.h"
#include "Core/FileIO.h"
#include <iostream>
using namespace std;

int main()
{

	cout << kiko::getFilePath() << endl;
	kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 5; i++) 
	{
		cout << kiko::random(1,5) << endl;
	}
	
}