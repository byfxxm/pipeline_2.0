#include "pch.h"
#include "g_processer_derive.h"

void GProcesserDerive::G0(int line, Tag* tags, int count) {
	Print(line, tags, count);
}

void GProcesserDerive::G1(int line, Tag* tags, int count) {
	Print(line, tags, count);
}

void GProcesserDerive::G2(int line, Tag* tags, int count) {
	Print(line, tags, count);
}

void GProcesserDerive::G3(int line, Tag* tags, int count) {
	Print(line, tags, count);
}

void GProcesserDerive::Print(int line, Tag* tags, int count) {
	std::cout << "line " << line << ": ";
	for (int i = 0; i < count; ++i) {
		std::cout << (char)tags[i].token << tags[i].value << " ";
	}
	std::cout << std::endl;
}