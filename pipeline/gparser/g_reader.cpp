#include "pch.h"
#include "g_reader.h"

GReader::GReader(const std::filesystem::path& path) {
	fin_.open(path);
	assert(fin_.is_open());
}

GReader::~GReader() {
	fin_.close();
}

std::optional<std::vector<Tag>> GReader::NextLine() {
	std::optional<std::vector<Tag>> ret;
	++cur_line_no_;

	while (1) {
		auto next_tag = NextTag();
		if (!next_tag.has_value())
			break;
		ret.value().push_back(next_tag.value());
	}

	return ret;
}

std::optional<Tag> GReader::NextTag() {
	std::optional<Tag> ret;

	SkipSpace();
	auto token = NextToken();
	auto value = NextValue();

	if (!token.has_value() || !value.has_value())
		return ret;

	ret.emplace(token.value(), value.value());
	return ret;
}

std::optional<Token> GReader::NextToken() {
	std::optional<Token> ret;

	switch ((Token)cur_line_str_[cur_line_cursor_]) {
	case Token::kG:
	case Token::kX:
	case Token::kY:
	case Token::kZ:
		ret.emplace((Token)cur_line_str_[cur_line_cursor_++]);
		break;
	default:
		break;
	}

	return ret;
}

std::optional<double> GReader::NextValue() {
	std::optional<double> ret;
	std::string value;

	while (std::isdigit(cur_line_str_[cur_line_cursor_]) || cur_line_str_[cur_line_cursor_] == '.') {
		value.push_back(cur_line_str_[cur_line_cursor_]);
		++cur_line_cursor_;
	}

	ret = std::stod(value);
	return ret;
}

void GReader::SkipSpace() {
	while (std::isspace(cur_line_str_[cur_line_cursor_]))
		++cur_line_cursor_;
}

int GReader::GetCurLineNo() const {
	return cur_line_no_;
}