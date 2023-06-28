#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include <iostream>
using namespace std;

int main()
{
	
	int* p = new int;
	
	delete p;


	cout << "Get File Path: " << kiko::getFilePath() << endl;

	kiko::setFilePath("Assets");
	cout << "Get File Path. New file path set: " << kiko::getFilePath() << endl;

	size_t size;
	kiko::getFileSize("game.txt", size);
	cout << "Get File Size: " << size << endl;


	std::string s;
	kiko::readFile("game.txt", s);
	cout << "Read File: " << s << endl;

	kiko::seedRandom((unsigned int)time(nullptr));
	cout << "Random: ";
	for (int i = 0; i < 5; i++) 
	{
		cout << kiko::random(1,5) << endl;
	}
	
}