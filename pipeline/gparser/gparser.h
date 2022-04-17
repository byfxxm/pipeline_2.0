#pragma once

#ifdef GPARSER_EXPORTS
#define GPARSER_API __declspec(dllexport)
#else
#define GPARSER_API __declspec(dllimport)
#endif

enum class Token {
	kG = 'G',
	kX = 'X',
	kY = 'Y',
	kZ = 'Z',
};

struct Tag {
	Token token;
	double value;
};

class GProcesser {
public:
	virtual void G0(int, Tag*, int) = 0;
	virtual void G1(int, Tag*, int) = 0;
	virtual void G2(int, Tag*, int) = 0;
	virtual void G3(int, Tag*, int) = 0;
};

extern "C" {
	GPARSER_API void* gparser_create(const char*, GProcesser*);
	GPARSER_API void gparser_delete(void*);
	GPARSER_API void gparser_parse(void*);
}