#include "pch.h"
#include "gparser_imp.h"

GLine::GLine(const std::string& line_str) : str_(line_str) {}

inline std::optional<char> GLine::Current() {
	assert(cursor_ <= str_.size());
	return cursor_ == str_.size() ? std::nullopt : std::optional<char>(str_[cursor_]);
}

inline void GLine::Next() {
	if (!Current().has_value())
		assert(0);

	++cursor_;
}

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

void GparserImp::Parse() {
	while (1) {
		auto line_op = NextLine();
		if (!line_op.has_value())
			break;

		auto line = line_op.value();
		bool has_called = false;
		for (const auto& it : line) {
			std::stringstream tag;
			tag << (char)it.token << it.value;
			auto tag_it = kProcessFuncs.find(tag.str());
			if (tag_it != kProcessFuncs.end()) {
				(g_processer_->*tag_it->second)(line_no_, line.data(), line.size());
				has_called = true;
				last_motion_ = tag.str();
				break;
			}
		}

		if (!has_called && !line_op.value().empty())
			(g_processer_->*kProcessFuncs.find(last_motion_)->second)(line_no_, line.data(), line.size());
	}
}

std::optional<std::vector<Tag>> GparserImp::NextLine() {
	if (fin_.eof())
		return std::nullopt;

	++line_no_;
	std::string line;
	std::getline(fin_, line);
	g_line_.~GLine();
	new(&g_line_) GLine(line);
	std::vector<Tag> ret;

	while (1) {
		auto next_tag = NextTag();
		if (!next_tag.has_value())
			break;

		ret.push_back(next_tag.value());
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
	auto ch_op = g_line_.Current();
	if (!ch_op.has_value())
		return std::nullopt;

	g_line_.Next();
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

	while ((ch_op = g_line_.Current()).has_value()) {
		auto ch = ch_op.value();
		if (!std::isdigit(ch) && ch != '.')
			break;
		value.push_back(ch);
		g_line_.Next();
	}

	return value.empty() ? std::nullopt : std::optional<double>(std::stod(value));
}

void GparserImp::SkipSpace() {
	std::optional<char> ch_op;
	while ((ch_op = g_line_.Current()).has_value() && std::isspace(ch_op.value())) {
		g_line_.Next();
	}
}