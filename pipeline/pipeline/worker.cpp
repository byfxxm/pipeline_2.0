#include "pch.h"
#include "pipeline_imp.h"

void Worker::Write(std::shared_ptr<Code> code) {
	if (pipeline_->stop_)
		return;

	if (index_ == pipeline_->workers_.size() - 1) {
		while (pipeline_->pause_)
			std::this_thread::yield();
		if (pipeline_->output_switch_)
			pipeline_->output_switch_->Write(code);
		return;
	}

	pipeline_->workers_[index_ + 1]->Do(code);
}