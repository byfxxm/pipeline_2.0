#pragma once

#ifdef GWORKER_EXPORTS
#define GWORKER_API __declspec(dllexport)
#else
#define GWORKER_API __declspec(dllimport)
#endif

extern "C" {
	GWORKER_API void* gworker_create();
	GWORKER_API void gworker_delete(void*);
	GWORKER_API bool gworker_load_file(void*, const char*);
	GWORKER_API void gworker_unload_file(void*);
}