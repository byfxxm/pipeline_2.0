#pragma once
#include "pipeline.h"

class Worker;
class PipelineImp final {
public:
	~PipelineImp();
	void AddProcedure(Procedure);
	void Start();
	void Stop();

private:
	std::vector<Worker*> workers_;
};