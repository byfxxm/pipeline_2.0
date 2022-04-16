#include "pch.h"
#include "pipeline.h"
#include "pipeline_imp.h"

void* pipeline_create() {
	return new PipelineImp();
}

void pipeline_delete(void* p) {
	delete (PipelineImp*)p;
}

void pipeline_add_worker(void* p, Worker* worker) {
	return ((PipelineImp*)p)->AddWorker(worker);
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

void pipeline_set_output_switch(void* p, OutputSwitch* sw) {
	return ((PipelineImp*)p)->SetOutputSwitch(sw);
}

bool pipeline_is_idle(void* p) {
	return ((PipelineImp*)p)->IsIdle();
}