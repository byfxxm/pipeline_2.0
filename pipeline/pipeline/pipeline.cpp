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

void pipeline_start(void* p) {
	return ((PipelineImp*)p)->Start();
}

void pipeline_stop(void* p) {
	return ((PipelineImp*)p)->Stop();
}