#include "pch.h"
#include "pipeline_imp.h"

void Worker::Write(Code* code) {
	std::unique_lock<std::mutex> lock(pipeline_->mtx_);
	if (pipeline_->stop_)
		return;

	if (index_ == pipeline_->workers_.size() - 1) {
		pipeline_->cv_.wait(lock, [this]() {return !pipeline_->pause_; });
		if (pipeline_->output_switch_)
			pipeline_->output_switch_->Write(code);
		return;
	}

	pipeline_->cv_.wait(lock, [this]() {return !pipeline_->pause_; });
	pipeline_->workers_[index_ + 1]->Do(code);
}