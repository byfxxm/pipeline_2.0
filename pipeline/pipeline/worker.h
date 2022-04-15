#pragma once
#include "pipeline.h"

class Worker {
	friend class PipelineImp;

public:
	Worker(const PipelineImp*, size_t, Procedure);
	~Worker() = default;
	void Do(Code*);
	void Write(Code*);

private:
	const PipelineImp* pipeline_{ nullptr };
	size_t index_{ 0 };
	Procedure procedure_{ nullptr };
};