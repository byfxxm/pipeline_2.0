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

void pipeline_add_procedure(void* p, procedure proc)
{
	return ((pipeline_imp*)p)->add_procedure(proc);
}

void pipeline_start(void* p)
{
	return ((pipeline_imp*)p)->start();
}

void pipeline_stop(void* p)
{
	return ((pipeline_imp*)p)->stop();
}