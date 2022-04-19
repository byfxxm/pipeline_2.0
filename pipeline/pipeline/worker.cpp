#include "pch.h"
#include "pipeline_imp.h"

PIPELINE_BEGIN
void Worker::Write(Code* code) {
	if (pipeline_->stop_)
		return;

	if (index_ == pipeline_->workers_.size() - 1) {
		if (pipeline_->output_switch_)
			pipeline_->output_switch_->Write(code);
		return;
	}

	pipeline_->workers_[index_ + 1]->Do(code);
}
PIPELINE_END