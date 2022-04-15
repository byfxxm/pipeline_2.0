#include "pch.h"
#include "pipeline.h"
#include "pipeline_imp.h"

void* pipeline_create()
{
	return new PipelineImp();
}

void pipeline_delete(void* p)
{
	delete p;
}

void pipeline_add_worker(void* p, Worker* w)
{
	return ((PipelineImp*)p)->add_worker(w);
}

void pipeline_start(void* p)
{
	return ((PipelineImp*)p)->start();
}

void pipeline_stop(void* p)
{
	return ((PipelineImp*)p)->stop();
}