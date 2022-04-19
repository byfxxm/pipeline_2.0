#pragma once
#include "gparser.h"

class GLine {
public:
	GLine() = default;
	GLine(const std::string&);
	std::optional<char> Current();
	void Next();

private:
	std::string str_;
	size_t cursor_{ 0 };
};

class GparserImp {
private:
	using ProcessFunc = void(GProcesser::*)(size_t, Tag*, size_t);
	static const std::unordered_map<std::string, ProcessFunc> kProcessFuncs;

public:
	GparserImp(const std::filesystem::path&, GProcesser*);
	void Parse();

private:
	std::optional<std::vector<Tag>> NextLine();
	std::optional<Tag> NextTag();
	std::optional<Token> NextToken();
	std::optional<double> NextValue();
	void SkipSpace();

private:
	std::ifstream fin_;
	size_t line_no_{ 0 };
	GLine g_line_;
	GProcesser* g_processer_{ nullptr };
	std::string last_motion_{ "G0" };
};