#pragma once

#ifdef PIPELINE_EXPORTS
#define PIPELINE_API __declspec(dllexport)
#else
#define PIPELINE_API __declspec(dllimport)
#endif

struct Code {
	int value;
};
class Worker;
struct Utils {
	using Write = void(Worker::*)(Code*);
	Worker* worker;
	Write write;
};
using Procedure = void(*)(Utils*, Code*);

class OutputSwitch {
public:
	virtual bool Write(const Code*) = 0;
};

extern "C"
{
	PIPELINE_API void* pipeline_create();
	PIPELINE_API void pipeline_delete(void*);
	PIPELINE_API void pipeline_add_procedure(void*, Procedure);
	PIPELINE_API void pipeline_start_async(void*);
	PIPELINE_API void pipeline_stop_async(void*);
	PIPELINE_API void pipeline_wait_for_idle(void*);
	PIPELINE_API void pipeline_set_output_switch(void*, OutputSwitch*);
}