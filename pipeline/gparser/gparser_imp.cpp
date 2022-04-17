#include "pch.h"
#include "gparser_imp.h"

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
	std::getline(fin_, cur_line_str_);

	while (1) {
		auto next_tag = NextTag();
		if (!next_tag.has_value())
			break;

		if (!ret.has_value())
			ret.emplace();
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
		return std::nullopt;

	return Tag(token.value(), value.value());
}

std::optional<Token> GReader::NextToken() {
	auto ch_op = NextChar();
	if (!ch_op.has_value())
		return std::nullopt;

	switch ((Token)ch_op.value()) {
	case Token::kG:
	case Token::kX:
	case Token::kY:
	case Token::kZ:
		return (Token)ch_op.value();
	default:
		break;
	}

	return std::nullopt;
}

std::optional<double> GReader::NextValue() {
	std::string value;
	std::optional<char> ch_op;

	while ((ch_op = PeekChar()).has_value()) {
		auto ch = ch_op.value();
		if (!std::isdigit(ch) && ch != '.')
			break;
		value.push_back(ch);
		NextChar();
	}

	return value.empty() ? std::nullopt : std::optional<double>(std::stod(value));
}

inline std::optional<char> GReader::NextChar() {
	auto ch_op = PeekChar();

	if (!ch_op.has_value())
		return std::nullopt;

	++cur_line_cursor_;
	return ch_op;
}

inline std::optional<char> GReader::PeekChar() {
	if (cur_line_cursor_ == cur_line_str_.size())
		return std::nullopt;

	return cur_line_str_[cur_line_cursor_];
}

void GReader::SkipSpace() {
	std::optional<char> ch_op;
	while ((ch_op = PeekChar()).has_value() && std::isspace(ch_op.value())) {
		NextChar();
	}
}

int GReader::GetCurLineNo() const {
	return cur_line_no_;
}