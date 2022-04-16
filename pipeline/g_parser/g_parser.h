#pragma once
//#include <unordered_map>

#ifdef GPARSER_EXPORTS
#define GPARSER_API __declspec(dllexport)
#else
#define GPARSER_API __declspec(dllimport)
#endif

enum class Token {
	kX,
	kY,
	kZ,
};

namespace std {
	template<typename Key, typename Value>
	class unordered_map;
}

class Command {
public:
	using Data = std::unordered_map<Token, double>;
	virtual void G0(Data*) = 0;
};

extern "C" {
	GPARSER_API Worker* g_create();
	GPARSER_API void g_delete(Worker*);
}