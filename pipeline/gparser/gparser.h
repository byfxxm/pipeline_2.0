#pragma once

#ifdef GPARSER_EXPORTS
#define GPARSER_API __declspec(dllexport)
#else
#define GPARSER_API __declspec(dllimport)
#endif

namespace gparser {
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
		virtual ~GProcesser() = default;
		virtual void G0(size_t, Tag*, size_t) = 0;
		virtual void G1(size_t, Tag*, size_t) = 0;
		virtual void G2(size_t, Tag*, size_t) = 0;
		virtual void G3(size_t, Tag*, size_t) = 0;
	};
}

extern "C" {
	GPARSER_API void* gparser_create(const char*, gparser::GProcesser*);
	GPARSER_API void gparser_delete(void*);
	GPARSER_API void gparser_parse(void*);
}