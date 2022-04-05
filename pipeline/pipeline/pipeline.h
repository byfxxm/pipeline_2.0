#pragma once

#ifdef PIPELINE_EXPORTS
#define PIPELINE_API __declspec(dllexport)
#else
#define PIPELINE_API __declspec(dllimport)
#endif

struct code {};

class PIPELINE_API worker
{
	friend class pipeline_imp;

public:
	virtual void process(code*) = 0;
	virtual void write(code*);

private:
	void* _pipeline{ nullptr };
	size_t _index{ 0 };
};

extern "C"
{
	PIPELINE_API void* pipeline_create();
	PIPELINE_API void pipeline_delete(void*);
	PIPELINE_API void pipeline_add_worker(void*, worker*);
	PIPELINE_API void pipeline_start(void*);
	PIPELINE_API void pipeline_stop(void*);
}