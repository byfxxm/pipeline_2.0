#pragma once
#include "pipeline.h"

class Worker {
	friend class PipelineImp;

public:
	Worker(Procedure);
	~Worker() = default;
	void Do(Code*);
	void Write(Code*);

private:
	Procedure procedure_{ nullptr };
	int index_{ 0 };
};