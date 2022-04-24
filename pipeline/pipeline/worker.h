#pragma once
#include "pipeline.h"

namespace pipeline {
	class PIPELINE_API Worker {
	public:
		virtual ~Worker() = default;
		virtual void Do(Code*) = 0;
		void Write(Code*);

	private:
		friend class PipelineImp;
		PipelineImp* pipeline_{ nullptr };
		size_t index_{ 0 };
	};

	class OutputSwitch {
	public:
		virtual void Write(Code*) = 0;
	};
}