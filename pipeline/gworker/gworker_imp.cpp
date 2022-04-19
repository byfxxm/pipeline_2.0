#include "pch.h"
#include "gworker_imp.h"

GWORKER_BEGIN
GworkerImp::~GworkerImp() {
	UnloadFile();
}

void GworkerImp::Do(pipeline::Code*) {
	assert(gparser_);
	gparser_parse(gparser_);
	Write(nullptr);
}

bool GworkerImp::LoadFile(const char* file) {
	if (!std::filesystem::is_regular_file(std::filesystem::path(file)))
		return false;

	gparser_delete(gparser_);
	gparser_ = gparser_create(file, &g_proc_der_);
	return true;
}

void GworkerImp::UnloadFile() {
	gparser_delete(gparser_);
	gparser_ = nullptr;
}

GWORKER_END