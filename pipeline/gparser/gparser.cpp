#include "pch.h"
#include "gparser.h"
#include "gparser_imp.h"

void* gparser_create(const char* file, GProcesser* proc) {
	return new GparserImp(file, proc);
}

void gparser_delete(void* p) {
	delete (GparserImp*)p;
}

void gparser_parse(void* p) {
	return ((GparserImp*)p)->Parse();
}