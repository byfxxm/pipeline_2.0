#include "pch.h"
#include "g_parser.h"
#include "g_parser_imp.h"

Worker* g_create() {
	return new GParserImp();
}

void g_delete(Worker* p) {
	delete p;
}