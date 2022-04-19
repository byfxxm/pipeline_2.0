#include "pch.h"
#include "gparser_worker_imp.h"

namespace gworker {
	GparserWorkerImp::~GparserWorkerImp() {
		UnloadFile();
	}

	void GparserWorkerImp::Do(pipeline::Code*) {
		assert(gparser_);
		gparser::gparser_parse(gparser_);
		Write(nullptr);
	}

	bool GparserWorkerImp::LoadFile(const char* file) {
		if (!std::filesystem::is_regular_file(std::filesystem::path(file)))
			return false;

		gparser::gparser_delete(gparser_);
		gparser_ = gparser_create(file, &g_proc_der_);
		return true;
	}

	void GparserWorkerImp::UnloadFile() {
		gparser::gparser_delete(gparser_);
		gparser_ = nullptr;
	}
}