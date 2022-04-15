#include "pch.h"
#include "pipeline.h"
#include "pipeline_imp.h"

void* pipeline_create() {
	return new PipelineImp();
}

void pipeline_delete(void* pipeline) {
	delete pipeline;
}

void pipeline_add_procedure(void* pipeline, Procedure proc) {
	return ((PipelineImp*)pipeline)->AddProcedure(proc);
}

void pipeline_start_async(void* pipeline) {
	return ((PipelineImp*)pipeline)->StartAsync();
}

void pipeline_stop_async(void* pipeline) {
	return ((PipelineImp*)pipeline)->StopAsync();
}

void pipeline_wait_for_idle(void* pipeline) {
	return ((PipelineImp*)pipeline)->WaitForIdle();
}