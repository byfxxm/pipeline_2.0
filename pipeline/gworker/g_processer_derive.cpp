#include "pch.h"
#include "g_processer_derive.h"
#include "gworker_imp.h"
#include "../pipeline/code.h"

GWORKER_BEGIN
GProcesserDerive::GProcesserDerive(GworkerImp& gworker) : gworker_(gworker) {}

void GProcesserDerive::G0(size_t line_no, gparser::Tag* tags, size_t count) {
	//Print(line_no, tags, count);

	auto move = new pipeline::Move();
	for (size_t i = 0; i < count; ++i) {
		switch (tags[i].token) {
		case gparser::Token::kX:
			move->end(0) = tags[i].value;
			break;
		case gparser::Token::kY:
			move->end(1) = tags[i].value;
			break;
		case gparser::Token::kZ:
			move->end(2) = tags[i].value;
			break;
		default:
			break;
		}
	}

	gworker_.Write(move);
}

void GProcesserDerive::G1(size_t line_no, gparser::Tag* tags, size_t count) {
	//Print(line_no, tags, count);

	auto line = new pipeline::Line();
	for (size_t i = 0; i < count; ++i) {
		switch (tags[i].token) {
		case gparser::Token::kX:
			line->end(0) = tags[i].value;
			break;
		case gparser::Token::kY:
			line->end(1) = tags[i].value;
			break;
		case gparser::Token::kZ:
			line->end(2) = tags[i].value;
			break;
		default:
			break;
		}
	}

	gworker_.Write(line);
}

void GProcesserDerive::G2(size_t line_no, gparser::Tag* tags, size_t count) {
	Print(line_no, tags, count);
}

void GProcesserDerive::G3(size_t line_no, gparser::Tag* tags, size_t count) {
	Print(line_no, tags, count);
}

void GProcesserDerive::Print(size_t line_no, gparser::Tag* tags, size_t count) {
	std::cout << "line " << line_no << ": ";
	for (size_t i = 0; i < count; ++i) {
		std::cout << (char)tags[i].token << tags[i].value << " ";
	}
	std::cout << std::endl;
}

GWORKER_END