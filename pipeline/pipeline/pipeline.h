#pragma once

#ifdef PIPELINE_EXPORTS
#define PIPELINE_API __declspec(dllexport)
#else
#define PIPELINE_API __declspec(dllimport)
#endif

struct Code {};

class PIPELINE_API Worker
{
	friend class PipelineImp;

public:
	virtual void process(Code*) = 0;
	virtual void write(Code*);

private:
	void* pipeline_{ nullptr };
	size_t index_{ 0 };
};

extern "C"
{
	PIPELINE_API void* pipeline_create();
	PIPELINE_API void pipeline_delete(void*);
	PIPELINE_API void pipeline_add_worker(void*, Worker*);
	PIPELINE_API void pipeline_start(void*);
	PIPELINE_API void pipeline_stop(void*);
}