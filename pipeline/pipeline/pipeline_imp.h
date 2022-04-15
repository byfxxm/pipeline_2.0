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
	void SetOutput(Output);

private:
	std::vector<Worker*> workers_;
	volatile bool stop_{ false };
	std::thread thread_;
	Output output_{ nullptr };
};