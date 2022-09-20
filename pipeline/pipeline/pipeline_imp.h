#pragma once
#include "pipeline.h"

namespace pipeline {
	class PipelineImp final {
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
		void Write(size_t, std::shared_ptr<Code>);

	private:
		std::vector<Worker*> workers_;
		volatile bool stop_{ false };
		volatile bool pause_{ false };
		std::thread thread_;
		OutputSwitch* output_switch_{ nullptr };
	};
}