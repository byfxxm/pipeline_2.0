#include "pch.h"
#include "pipeline_imp.h"
#include "worker.h"

PipelineImp::~PipelineImp() {
	for (auto it : workers_)
		delete it;
}

void PipelineImp::AddProcedure(Procedure proc) {
}

void PipelineImp::Start() {
}

void PipelineImp::Stop() {

}