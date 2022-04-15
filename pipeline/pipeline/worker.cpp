#include "pch.h"
#include "worker.h"
#include "pipeline_imp.h"

Worker::Worker(const PipelineImp* pipeline, size_t index, Procedure proc) : pipeline_(pipeline), index_(index), procedure_(proc) {}

void Worker::Do(Code* code) {
	assert(procedure_);
	Utils utils{ this, &Worker::Write };
	procedure_(&utils, code);
}

void Worker::Write(Code* code) {
	if (pipeline_->stop_ || index_ == pipeline_->workers_.size() - 1)
		return;

	pipeline_->workers_[index_ + 1]->Do(code);
}