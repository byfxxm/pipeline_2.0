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
	GPARSER_API Worker* gparser_create();
	GPARSER_API void gparser_delete(Worker*);
	GPARSER_API bool gparser_load_file(Worker*, const char*);
	GPARSER_API void gparser_unload_file(Worker*);
}