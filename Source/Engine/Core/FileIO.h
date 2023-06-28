#pragma once
#include <filesystem>
#include <string>
// dont use using namespace in headers. it forces everyone who uses that namespace to use it as well. 

namespace kiko
{
	std::string getFilePath();
}