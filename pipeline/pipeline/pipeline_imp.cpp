#include "pch.h"
#include "pipeline_imp.h"
#include "worker.h"

PipelineImp::~PipelineImp() {
	for (auto it : workers_)
		delete it;
}

void PipelineImp::AddProcedure(Procedure proc) {
	assert(proc);
	workers_.push_back(new Worker(this, workers_.size(), proc));
}

void PipelineImp::StartAsync() {
	stop_ = false;
	if (!workers_.empty()) {
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