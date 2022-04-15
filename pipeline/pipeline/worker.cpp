#include "pch.h"
#include "pipeline.h"
#include "pipeline_imp.h"

void Worker::write(Code* c)
{
	auto p = (PipelineImp*)pipeline_;

	if (index_ < p->workers_.size() - 1)
		p->workers_[index_ + 1]->process(c);
}