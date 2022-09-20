#pragma once
#include "g_processer_derive.h"

namespace gworker {
	class GworkerImp : public pipeline::Worker {
	public:
		using pipeline::Worker::Write;

	public:
		virtual ~GworkerImp() override;
		virtual void Do(std::shared_ptr<pipeline::Code>) override;
		bool LoadFile(const char*);
		void UnloadFile();

	private:
		void* gparser_{ nullptr };
		GProcesserDerive g_proc_der_{ *this };
	};
}