#pragma once
#include "pipeline.h"

class pipeline_imp
{
public:
	void add_procedure(procedure);
	void start();
	void stop();

private:
	static void _write(void*, code*);
	static void _write(code*);

private:
	std::vector<procedure> _procs;
	utils _utils{  };
	int _cur{ 0 };
};