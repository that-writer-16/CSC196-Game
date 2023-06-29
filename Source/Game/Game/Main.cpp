#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Renderer/Render.h"
#include <iostream>
using namespace std;

int main()
{
	kiko::g_memoryTracker.DisplayInfo();
	int* p = new int;
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	for (int i = 0; i < 10000000; i++){}
	cout << timer.GetElapsedMicroseconds() << endl;

	
	//cout << "Get File Path: " << kiko::getFilePath() << endl;

	//kiko::setFilePath("Assets");
	//cout << "Get File Path. New file path set: " << kiko::getFilePath() << endl;

	//size_t size;
	//kiko::getFileSize("game.txt", size);
	//cout << "Get File Size: " << size << endl;


	//std::string s;
	//kiko::readFile("game.txt", s);
	//cout << "Read File: " << s << endl;

	//kiko::seedRandom((unsigned int)time(nullptr));
	//cout << "Random: ";
	//for (int i = 0; i < 5; i++) 
	//{
	//	cout << kiko::random(1,5) << endl;
	//}
	
}