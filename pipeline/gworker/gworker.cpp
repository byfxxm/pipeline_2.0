#include "pch.h"
#include "gworker.h"
#include "gworker_imp.h"

void* gworker_create() {
	return new gworker::GparserWorkerImp();
}

void gworker_delete(void* p) {
	delete (gworker::GparserWorkerImp*)p;
}

bool gworker_load_file(void* p, const char* file) {
	return ((gworker::GparserWorkerImp*)p)->LoadFile(file);
}

void gworker_unload_file(void* p) {
	return ((gworker::GparserWorkerImp*)p)->UnloadFile();
}