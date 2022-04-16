#include "pch.h"
#include "gparser.h"
#include "gparser_worker.h"

Worker* g_create() {
	return new GparserWorker();
}

void g_delete(Worker* p) {
	delete p;
}