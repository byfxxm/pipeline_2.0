#pragma once
#include "pipeline.h"

class PipelineImp final
{
	friend class Worker;

public:
	void add_worker(Worker*);
	void start();
	void stop();

private:
	std::vector<Worker*> workers_;
};