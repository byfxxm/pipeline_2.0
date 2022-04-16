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

class Command {
public:
	struct Data {
		Token token;
		double value;
	};

	virtual void G0(Data*, int) = 0;
	virtual void G1(Data*, int) = 0;
	virtual void G2(Data*, int) = 0;
	virtual void G3(Data*, int) = 0;
};

extern "C" {
	GPARSER_API Worker* g_create();
	GPARSER_API void g_delete(Worker*);
}