#include "pch.h"
#include "pipeline_imp.h"

void PipelineImp::add_worker(Worker* w)
{
	w->index_ = workers_.size();
	w->pipeline_ = this;
	workers_.push_back(w);
}

void PipelineImp::start()
{
	if (workers_.empty())
		return;

	workers_[0]->process(nullptr);
}

void PipelineImp::stop()
{

}