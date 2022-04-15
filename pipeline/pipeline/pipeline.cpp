#include "pch.h"
#include "pipeline.h"
#include "pipeline_imp.h"

void* pipeline_create() {
	return new PipelineImp();
}

void pipeline_delete(void* p) {
	delete p;
}

void pipeline_add_procedure(void* p, Procedure proc) {
	return ((PipelineImp*)p)->AddProcedure(proc);
}

void pipeline_start_async(void* p) {
	return ((PipelineImp*)p)->StartAsync();
}

void pipeline_stop_async(void* p) {
	return ((PipelineImp*)p)->StopAsync();
}

void pipeline_wait_for_idle(void* p) {
	return ((PipelineImp*)p)->WaitForIdle();
}

void pipeline_set_output(void* p, Output output) {
	return ((PipelineImp*)p)->SetOutput(output);
}