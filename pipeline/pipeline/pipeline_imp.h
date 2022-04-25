#pragma once
#include "pipeline.h"

namespace pipeline {
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
		void Pause();
		void Resume();

	private:
		std::vector<Worker*> workers_;
		volatile bool stop_{ false };
		volatile bool pause_{ false };
		std::thread thread_;
		OutputSwitch* output_switch_{ nullptr };
	};
}