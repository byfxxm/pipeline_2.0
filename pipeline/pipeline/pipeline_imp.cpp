#include "pch.h"
#include "pipeline_imp.h"

void pipeline_imp::add_procedure(procedure proc)
{
	_procs.push_back(proc);
}

void pipeline_imp::start()
{
	if (_procs.empty())
		return;

	_procs[0](&_utils, new code());
}

void pipeline_imp::stop()
{

}

void pipeline_imp::_write(void* p, code* c)
{
	auto pipeline = (pipeline_imp*)p;
	pipeline->_procs[++pipeline->_cur](&pipeline->_utils, c);
}

void pipeline_imp::_write(code*)
{

}