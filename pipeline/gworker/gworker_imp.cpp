#include "pch.h"
#include "gworker_imp.h"

GworkerImp::~GworkerImp() {
	UnloadFile();
}

void GworkerImp::Do(std::shared_ptr<pipeline::Code>) {
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