#pragma once
#include <memory>

namespace pipeline {
	class Code;
	class PipelineImp;

	class PIPELINE_API Worker {
	public:
		virtual ~Worker() = default;
		virtual void Do(std::shared_ptr<Code>) = 0;
		void SetPipeline(PipelineImp*, size_t);

	protected:
		void Write(std::shared_ptr<Code>);

	private:
		PipelineImp* pipeline_{ nullptr };
		size_t index_{ 0 };
	};

	class OutputSwitch {
	public:
		virtual ~OutputSwitch() = default;
		virtual void Write(std::shared_ptr<Code>) = 0;
	};
}