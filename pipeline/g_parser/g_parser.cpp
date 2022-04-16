#include "pch.h"
#include "g_parser.h"
#include "g_parser_worker.h"

Worker* g_create() {
	return new GParserWorker();
}

void g_delete(Worker* p) {
	delete p;
}