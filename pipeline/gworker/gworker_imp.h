#pragma once
#include "g_processer_derive.h"

GWORKER_BEGIN
class GworkerImp : public pipeline::Worker {
public:
	virtual ~GworkerImp() override;
	virtual void Do(pipeline::Code*) override;
	bool LoadFile(const char*);
	void UnloadFile();

private:
	void* gparser_{ nullptr };
	GProcesserDerive g_proc_der_{ *this };
};
GWORKER_END