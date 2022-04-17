#include "pch.h"
#include "g_processer_derive.h"

void GProcesserDerive::G0(int line, Tag* tags, int count) {
	Print("G0", line, tags, count);
}

void GProcesserDerive::G1(int line, Tag* tags, int count) {
	Print("G1", line, tags, count);
}

void GProcesserDerive::G2(int line, Tag* tags, int count) {
	Print("G2", line, tags, count);
}

void GProcesserDerive::G3(int line, Tag* tags, int count) {
	Print("G3", line, tags, count);
}

void GProcesserDerive::Print(const std::string& tag_str, int line, Tag* tags, int count) {
	std::cout << "line " << line << ": ";
	for (int i = 0; i < count; ++i) {
		std::cout << (char)tags[i].token << tags[i].value << " ";
	}
	std::cout << std::endl;
}