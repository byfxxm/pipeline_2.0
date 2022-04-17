#include "pch.h"
#include "gparser.h"
#include "gparser_worker.h"
#include "g_reader.h"

void GparserWorker::Do(Code*) {
	try {
		while (reader_->NextLine().has_value());
	}
	catch (const char* err) {
		std::cout << err << std::endl;
	}

	Write(nullptr);
}

bool GparserWorker::LoadFile(const char* file) {
	std::filesystem::path path(file);
	if (!std::filesystem::is_regular_file(path))
		return false;

	delete reader_;
	reader_ = new GReader(path);
	return true;
}

void GparserWorker::UnloadFile() {
	delete reader_;
	reader_ = nullptr;
}

