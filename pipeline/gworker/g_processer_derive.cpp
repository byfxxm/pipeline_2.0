#include "pch.h"
#include "g_processer_derive.h"
#include "gworker_imp.h"
#include "../pipeline/code.h"

GProcesserDerive::GProcesserDerive(GworkerImp& gworker) :gworker_(gworker) {}

void GProcesserDerive::G0(size_t line_no, gparser::Tag* tags, size_t count) {
	gworker_.Write(new pipeline::Move(TagsToAxesDouble(tags, count)));
}

void GProcesserDerive::G1(size_t line_no, gparser::Tag* tags, size_t count) {
	gworker_.Write(new pipeline::Line(TagsToAxesDouble(tags, count)));
}

void GProcesserDerive::G2(size_t line_no, gparser::Tag* tags, size_t count) {
	Print(line_no, tags, count);
}

void GProcesserDerive::G3(size_t line_no, gparser::Tag* tags, size_t count) {
	Print(line_no, tags, count);
}

void GProcesserDerive::Print(size_t line_no, gparser::Tag* tags, size_t count) {
	std::cout << "line no." << line_no << ": ";
	for (size_t i = 0; i < count; ++i) {
		std::cout << (char)tags[i].token << tags[i].value << " ";
	}
	std::cout << std::endl;
}

pipeline::AxesDouble GProcesserDerive::TagsToAxesDouble(gparser::Tag* tags, size_t count) {
	pipeline::AxesDouble ret{ pipeline::kAxesNum };

	for (size_t i = 0; i < count; ++i) {
		switch (tags[i].token) {
		case gparser::Token::kX:
			ret(0) = tags[i].value;
			break;
		case gparser::Token::kY:
			ret(1) = tags[i].value;
			break;
		case gparser::Token::kZ:
			ret(2) = tags[i].value;
			break;
		default:
			break;
		}
	}

	return ret;
}