#pragma once

#ifdef GPARSERWORKER_EXPORTS
#define GPARSERWORKER_API __declspec(dllexport)
#else
#define GPARSERWORKER_API __declspec(dllimport)
#endif

namespace gworker {
	extern "C" {
		GPARSERWORKER_API void* gworker_create();
		GPARSERWORKER_API void gworker_delete(void*);
		GPARSERWORKER_API bool gworker_load_file(void*, const char*);
		GPARSERWORKER_API void gworker_unload_file(void*);
	}
}