#include "pch.h"
#include "pipeline.h"
#include "pipeline_imp.h"

void* pipeline_create()
{
	return new pipeline_imp();
}

void pipeline_delete(void* p)
{
	delete p;
}

void pipeline_add_worker(void* p, worker* w)
{
	return ((pipeline_imp*)p)->add_worker(w);
}

void pipeline_start(void* p)
{
	return ((pipeline_imp*)p)->start();
}

void pipeline_stop(void* p)
{
	return ((pipeline_imp*)p)->stop();
}