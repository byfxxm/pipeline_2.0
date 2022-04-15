#pragma once
#include "pipeline.h"

class Worker;
class PipelineImp final {
	friend class Worker;

public:
	~PipelineImp();
	void AddProcedure(Procedure);
	void StartAsync();
	void StopAsync();
	void WaitForIdle();

private:
	std::vector<Worker*> workers_;
	volatile bool stop_{ false };
	std::thread thread_;
};