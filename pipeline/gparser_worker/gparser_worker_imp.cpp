#include "pch.h"
#include "gparser_worker_imp.h"

void GparserWorkerImp::Do(Code*) {
	gparser_parse(gparser_);
	Write(nullptr);
}

bool GparserWorkerImp::LoadFile(const char* file) {
	std::filesystem::path path(file);
	if (!std::filesystem::is_regular_file(path))
		return false;

	gparser_delete(gparser_);
	gparser_ = gparser_create(file, &g_proc_der_);
	return true;
}

void GparserWorkerImp::UnloadFile() {
	gparser_delete(gparser_);
	gparser_ = nullptr;
}