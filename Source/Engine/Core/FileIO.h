#pragma once
#include <filesystem>
#include <string>
// dont use using namespace in headers. it forces everyone who uses that namespace to use it as well. 

namespace kiko
{
	std::string getFilePath();
	bool setFilePath(const std::filesystem::path& path);
	bool fileExists(const std::filesystem::path& path);
	bool getFileSize(const std::filesystem::path& path, size_t& size);
	bool readFile(const std::filesystem::path& path, std::string& buffer);
}