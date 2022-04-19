#include "pch.h"
#include "gparser.h"
#include "gparser_imp.h"

void* gparser_create(const char* file, gparser::GProcesser* proc) {
	return new gparser::GparserImp(file, proc);
}

void gparser_delete(void* p) {
	delete (gparser::GparserImp*)p;
}

void gparser_parse(void* p) {
	return ((gparser::GparserImp*)p)->Parse();
}