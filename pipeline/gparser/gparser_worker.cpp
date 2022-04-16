#include "pch.h"
#include "gparser_worker.h"

void GparserWorker::Do(Code*) {
	std::string line;
	std::getline(fin_, line);
	
	for (auto c : line) {
		std::cout << c << std::endl;
	}
}

bool GparserWorker::LoadFile(const char* file) {
	if (!std::filesystem::is_regular_file(std::filesystem::path(file)))
		return false;

	fin_.open(file);
	assert(fin_.is_open());
	return true;
}

void GparserWorker::UnloadFile() {
	if (fin_.is_open())
		fin_.close();
}