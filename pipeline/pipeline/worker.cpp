#include "pch.h"
#include "pipeline_imp.h"

void Worker::Write(std::shared_ptr<Code> code) {
	pipeline_->Write(index_, code);
}

void Worker::SetPipeline(PipelineImp* pipeline, size_t index) {
	pipeline_ = pipeline;
	index_ = index;
}
