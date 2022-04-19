#include "pch.h"
#include "gparser_worker.h"
#include "gparser_worker_imp.h"

GWORKER_BEGIN
void* gworker_create() {
	return new GparserWorkerImp();
}

void gworker_delete(void* p) {
	delete (GparserWorkerImp*)p;
}

bool gworker_load_file(void* p, const char* file) {
	return ((GparserWorkerImp*)p)->LoadFile(file);
}

void gworker_unload_file(void* p) {
	return ((GparserWorkerImp*)p)->UnloadFile();
}

GWORKER_END