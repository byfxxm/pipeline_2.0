#pragma once
#include "gparser.h"

class GReader {
public:
	GReader(const std::filesystem::path&);
	~GReader();
	std::optional<std::vector<Tag>> NextLine();
	std::optional<Tag> NextTag();
	std::optional<Token> NextToken();
	std::optional<double> NextValue();
	void SkipSpace();
	int GetCurLineNo() const;

private:
	std::ifstream fin_;
	int cur_line_no_{ 0 };
	std::string cur_line_str_;
	int cur_line_cursor_{ 0 };
};