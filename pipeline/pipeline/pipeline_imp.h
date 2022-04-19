#pragma once
#include "pipeline.h"

namespace pipeline {
	class Worker;
	class PipelineImp final {
		friend class Worker;

	public:
		~PipelineImp();
		void AddWorker(Worker*);
		void StartAsync();
		void StopAsync();
		void WaitForIdle();
		void SetOutputSwitch(OutputSwitch* sw);
		bool IsIdle();

	private:
		std::vector<Worker*> workers_;
		volatile bool stop_{ false };
		std::thread thread_;
		OutputSwitch* output_switch_{ nullptr };
	};
}