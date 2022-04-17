#include "pch.h"
#include "g_processer_derive.h"

void GProcesserDerive::G0(size_t line, Tag* tags, size_t count) {
	Print(line, tags, count);
}

void GProcesserDerive::G1(size_t line, Tag* tags, size_t count) {
	Print(line, tags, count);
}

void GProcesserDerive::G2(size_t line, Tag* tags, size_t count) {
	Print(line, tags, count);
}

void GProcesserDerive::G3(size_t line, Tag* tags, size_t count) {
	Print(line, tags, count);
}

void GProcesserDerive::Print(size_t line, Tag* tags, size_t count) {
	std::cout << "line " << line << ": ";
	for (size_t i = 0; i < count; ++i) {
		std::cout << (char)tags[i].token << tags[i].value << " ";
	}
	std::cout << std::endl;
}