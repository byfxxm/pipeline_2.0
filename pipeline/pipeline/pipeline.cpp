#include "pch.h"
#include "pipeline.h"
#include "pipeline_imp.h"

const int pipeline::kAxesNum = 6;

void* pipeline_create() {
	return new pipeline::PipelineImp();
}

void pipeline_delete(void* p) {
	delete (pipeline::PipelineImp*)p;
}

void pipeline_add_worker(void* p, void* worker) {
	return ((pipeline::PipelineImp*)p)->AddWorker((pipeline::Worker*)worker);
}

void pipeline_start_async(void* p) {
	return ((pipeline::PipelineImp*)p)->StartAsync();
}

void pipeline_stop_async(void* p) {
	return ((pipeline::PipelineImp*)p)->StopAsync();
}

void pipeline_wait_for_idle(void* p) {
	return ((pipeline::PipelineImp*)p)->WaitForIdle();
}

void pipeline_set_output_switch(void* p, pipeline::OutputSwitch* sw) {
	return ((pipeline::PipelineImp*)p)->SetOutputSwitch(sw);
}

bool pipeline_is_idle(void* p) {
	return ((pipeline::PipelineImp*)p)->IsIdle();
}