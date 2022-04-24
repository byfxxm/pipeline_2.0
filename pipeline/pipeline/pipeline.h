#pragma once

#ifdef PIPELINE_EXPORTS
#define PIPELINE_API __declspec(dllexport)
#else
#define PIPELINE_API __declspec(dllimport)
#endif

#include "code.h"
#include "worker.h"

extern "C" {
	PIPELINE_API void* pipeline_create();
	PIPELINE_API void pipeline_delete(void*);
	PIPELINE_API void pipeline_add_worker(void*, void*);
	PIPELINE_API void pipeline_start_async(void*);
	PIPELINE_API void pipeline_stop_async(void*);
	PIPELINE_API void pipeline_wait_for_idle(void*);
	PIPELINE_API void pipeline_set_output_switch(void*, pipeline::OutputSwitch*);
	PIPELINE_API bool pipeline_is_idle(void*);
}