#pragma once
#include "g_processer_derive.h"

namespace gworker {
	class GparserWorkerImp : public pipeline::Worker {
	public:
		virtual ~GparserWorkerImp() override;
		virtual void Do(pipeline::Code*) override;
		bool LoadFile(const char*);
		void UnloadFile();

	private:
		void* gparser_{ nullptr };
		GProcesserDerive g_proc_der_{ *this };
	};
}