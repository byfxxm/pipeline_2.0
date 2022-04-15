#include "pch.h"
#include "worker.h"

Worker::Worker(Procedure proc) :procedure_(proc) {}

void Worker::Do(Code* code) {
	assert(procedure_);
	Utils utils{ this, &Worker::Write };
	procedure_(code, &utils);
}

void Worker::Write(Code* code) {
}

//void Worker::Write(void* worker, Code* code) {
//	return ((Worker*)worker)->Write(code);
//}