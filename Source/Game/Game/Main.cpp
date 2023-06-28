#include "Core/Random.h"
#include "Core/FileIO.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "Get File Path: "; 
	cout << kiko::getFilePath() << endl;

	kiko::setFilePath("Assets");
	cout << "Get File Path. New file path set: ";
	cout << kiko::getFilePath() << endl;

	size_t size;
	cout << "Get File Size: ";
	kiko::getFileSize("game.txt", size);
	cout << size << endl;


	std::string s;
	cout << "Read File: ";
	kiko::readFile("game.txt", s);
	cout << s << endl;

	kiko::seedRandom((unsigned int)time(nullptr));
	cout << "Random: ";
	for (int i = 0; i < 5; i++) 
	{
		cout << kiko::random(1,5) << endl;
	}
	
}