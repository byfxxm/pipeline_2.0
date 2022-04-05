#pragma once
#include "pipeline.h"

class pipeline_imp final
{
	friend class worker;

public:
	void add_worker(worker*);
	void start();
	void stop();

private:
	std::vector<worker*> _workers;
};