#include "pch.h"
#include "gparser.h"
#include "gparser_worker.h"

Worker* gparser_create() {
	return new GparserWorker();
}

void gparser_delete(Worker* p) {
	delete p;
}

bool gparser_load_file(Worker* p, const char* file) {
	return ((GparserWorker*)p)->LoadFile(file);
}