#include "pch.h"
#include "gparser_imp.h"

const std::unordered_map<std::string, GparserImp::ProcessFunc> GparserImp::kProcessFuncs = {
	{"G0", &GProcesser::G0},
	{"G1", &GProcesser::G1},
	{"G2", &GProcesser::G2},
	{"G3", &GProcesser::G3},
};

GparserImp::GparserImp(const std::filesystem::path& path, GProcesser* proc) : g_processer_(proc) {
	fin_.open(path);
	assert(fin_.is_open());
	assert(g_processer_);
}

GparserImp::~GparserImp() {
	fin_.close();
}

void GparserImp::Parse() {
	while (1) {
		auto line_op = NextLine();
		if (!line_op.has_value())
			break;

		auto line = line_op.value();
		for (const auto& it : line) {
			std::stringstream tag;
			tag << (char)it.token << it.value;
			auto tag_it = kProcessFuncs.find(tag.str());
			if (tag_it != kProcessFuncs.end())
				(g_processer_->*tag_it->second)(line_no_, line.data(), line.size());
		}
	}
}

GparserImp::Line GparserImp::NextLine() {
	std::optional<std::vector<Tag>> ret;

	if (fin_.eof())
		return ret;

	++line_no_;
	cur_line_cursor_ = 0;
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

std::optional<Tag> GparserImp::NextTag() {
	std::optional<Tag> ret;

	SkipSpace();
	auto token = NextToken();
	auto value = NextValue();

	if (!token.has_value() || !value.has_value())
		return std::nullopt;

	return Tag(token.value(), value.value());
}

std::optional<Token> GparserImp::NextToken() {
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

std::optional<double> GparserImp::NextValue() {
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

inline std::optional<char> GparserImp::NextChar() {
	auto ch_op = PeekChar();

	if (!ch_op.has_value())
		return std::nullopt;

	++cur_line_cursor_;
	return ch_op;
}

inline std::optional<char> GparserImp::PeekChar() {
	if (cur_line_cursor_ == cur_line_str_.size())
		return std::nullopt;

	return cur_line_str_[cur_line_cursor_];
}

void GparserImp::SkipSpace() {
	std::optional<char> ch_op;
	while ((ch_op = PeekChar()).has_value() && std::isspace(ch_op.value())) {
		NextChar();
	}
}