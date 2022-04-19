#include "pch.h"
#include "gworker.h"
#include "gworker_imp.h"

void* gworker_create() {
	return new GworkerImp();
}

void gworker_delete(void* p) {
	delete (GworkerImp*)p;
}

bool gworker_load_file(void* p, const char* file) {
	return ((GworkerImp*)p)->LoadFile(file);
}

void gworker_unload_file(void* p) {
	return ((GworkerImp*)p)->UnloadFile();
}