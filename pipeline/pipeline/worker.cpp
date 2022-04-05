#include "pch.h"
#include "pipeline.h"
#include "pipeline_imp.h"

void worker::write(code* c)
{
	auto p = (pipeline_imp*)_pipeline;

	if (_index < p->_workers.size() - 1)
		p->_workers[_index + 1]->process(c);
}