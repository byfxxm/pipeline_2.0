#pragma once
#include "g_processer_derive.h"

class GparserWorkerImp :public Worker {
public:
	virtual ~GparserWorkerImp() override = default;
	virtual void Do(Code*) override;
	bool LoadFile(const char*);
	void UnloadFile();

private:
	void* gparser_{ nullptr };
	GProcesserDerive g_proc_der_;
};