#pragma once
#include "gparser.h"

class GparserImp {
public:
	GparserImp(const std::filesystem::path&, GProcesser*);
	~GparserImp();
	void Parse();

private:
	using Line = std::optional<std::vector<Tag>>;
	using ProcessFunc = void(GProcesser::*)(int, Tag*, int);

private:
	Line NextLine();
	std::optional<Tag> NextTag();
	std::optional<Token> NextToken();
	std::optional<double> NextValue();
	void SkipSpace();
	std::optional<char> CurChar();
	std::optional<char> NextChar();

private:
	static const std::unordered_map<std::string, ProcessFunc> kProcessFuncs;
	std::ifstream fin_;
	size_t line_no_{ 0 };
	std::string cur_line_str_;
	size_t cur_line_cursor_{ 0 };
	GProcesser* g_processer_{ nullptr };
	std::string last_motion_;
};