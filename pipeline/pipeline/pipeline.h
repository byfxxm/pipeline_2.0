#pragma once

#ifdef PIPELINE_EXPORTS
#define PIPELINE_API __declspec(dllexport)
#else
#define PIPELINE_API __declspec(dllimport)
#endif

struct code {};
struct utils
{
	void (*write)(code*);
};

using procedure = void (*)(const utils*, code*);

extern "C"
{
	PIPELINE_API void* pipeline_create();
	PIPELINE_API void pipeline_delete(void*);
	PIPELINE_API void pipeline_add_procedure(void*, procedure);
	PIPELINE_API void pipeline_start(void*);
	PIPELINE_API void pipeline_stop(void*);
}