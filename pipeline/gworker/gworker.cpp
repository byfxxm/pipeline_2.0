#include "pch.h"
#include "gworker.h"
#include "gworker_imp.h"

void* gworker_create() {
	return new gworker::GworkerImp();
}

void gworker_delete(void* p) {
	delete (gworker::GworkerImp*)p;
}

bool gworker_load_file(void* p, const char* file) {
	return ((gworker::GworkerImp*)p)->LoadFile(file);
}

void gworker_unload_file(void* p) {
	return ((gworker::GworkerImp*)p)->UnloadFile();
}