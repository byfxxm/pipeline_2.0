#include "pch.h"
#include "pipeline_imp.h"

void pipeline_imp::add_worker(worker* w)
{
	w->_index = _workers.size();
	_workers.push_back(w);
}

void pipeline_imp::start()
{
	if (_workers.empty())
		return;

	_workers[0]->process(nullptr);
}

void pipeline_imp::stop()
{

}