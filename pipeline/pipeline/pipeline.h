#pragma once

#ifdef PIPELINE_EXPORTS
#define PIPELINE_API __declspec(dllexport)
#else
#define PIPELINE_API __declspec(dllimport)
#endif

#include "code.h"

namespace pipeline {
	class PIPELINE_API Worker {
	public:
		virtual ~Worker() = default;
		virtual void Do(Code*) = 0;
		void Write(Code*);

	private:
		friend class PipelineImp;
		const PipelineImp* pipeline_{ nullptr };
		size_t index_{ 0 };
	};

	class OutputSwitch {
	public:
		virtual void Write(Code*) = 0;
	};
}

extern "C"
{
	PIPELINE_API void* pipeline_create();
	PIPELINE_API void pipeline_delete(void*);
	PIPELINE_API void pipeline_add_worker(void*, void*);
	PIPELINE_API void pipeline_start_async(void*);
	PIPELINE_API void pipeline_stop_async(void*);
	PIPELINE_API void pipeline_wait_for_idle(void*);
	PIPELINE_API void pipeline_set_output_switch(void*, pipeline::OutputSwitch*);
	PIPELINE_API bool pipeline_is_idle(void*);
}