#include "pch.h"
#include "pipeline_imp.h"

PipelineImp::~PipelineImp() {
	StopAsync();
	WaitForIdle();
}

void PipelineImp::AddWorker(Worker* worker) {
	assert(worker);
	worker->SetPipeline(this, workers_.size());
	workers_.push_back(worker);
}

void PipelineImp::StartAsync() {
	if (IsIdle() && !workers_.empty()) {
		stop_ = false;
		pause_ = false;
		thread_ = std::thread([this]() {
			workers_[0]->Do(nullptr);
			});
	}
}

void PipelineImp::StopAsync() {
	stop_ = true;
}

void PipelineImp::WaitForIdle() {
	if (thread_.joinable())
		thread_.join();
}

void PipelineImp::SetOutputSwitch(OutputSwitch* sw) {
	output_switch_ = sw;
}

bool PipelineImp::IsIdle() {
	return !thread_.joinable();
}

void PipelineImp::Pause() {
	pause_ = true;
}

void PipelineImp::Resume() {
	pause_ = false;
}

void PipelineImp::Write(size_t index, std::shared_ptr<Code> code) {
	if (stop_)
		return;

	if (index == workers_.size() - 1) {
		while (pause_)
			std::this_thread::yield();
		if (output_switch_)
			output_switch_->Write(code);
		return;
	}

	workers_[index + 1]->Do(code);
}