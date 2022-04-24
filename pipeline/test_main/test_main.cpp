// test_main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>
#include "ring_buffer.h"
#include "../pipeline/pipeline.h"
#include "../gworker/gworker.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/pipeline.lib")
#pragma comment(lib, "../Debug/gworker.lib")
#else
#pragma comment(lib, "../Release/pipeline.lib")
#pragma comment(lib, "../Release/gworker.lib")
#endif

class Fifo final :public pipeline::OutputSwitch {
public:
	virtual void Write(pipeline::Code* code) override {
		while (!ring_buffer_.Write(code))
			std::this_thread::yield();
	}

	void Read(pipeline::Code*& code) {
		while (!ring_buffer_.Read(code))
			std::this_thread::yield();
	}

	bool IsEmpty() {
		return ring_buffer_.IsEmpty();
	}

private:
	RingBuffer<pipeline::Code*, 1000> ring_buffer_;
};

class WorkerMiddle :public pipeline::Worker {
public:
	virtual void Do(pipeline::Code* code) override {
		Write(code);
	}
};

class FirstWorker :public pipeline::Worker {
public:
	virtual void Do(pipeline::Code* code) override {
		while (1) {
			Write(new pipeline::Line{ pipeline::AxesDouble() });
		}
	}
};

void TestPipeline() {
	auto pipeline = pipeline_create();
#if 0
	auto first = gworker_create();
	gworker_load_file(gworker, "test1.nc");
#else
	auto first = new FirstWorker;
#endif
	WorkerMiddle workers[10];

	pipeline_add_worker(pipeline, first);
	for (auto& worker : workers)
		pipeline_add_worker(pipeline, &worker);

	Fifo fifo;
	pipeline_set_output_switch(pipeline, &fifo);
	pipeline_start_async(pipeline);

	std::thread mcc([&]() {
		pipeline::Code* code = nullptr;
		while (1) {
			fifo.Read(code);
			if (!code)
				break;

			if (code->Id() == pipeline::CodeId::kMove || code->Id() == pipeline::CodeId::kLine) {
				std::cout << "------>goto: ";
				for (size_t i = 0; i < pipeline::kAxesNum; ++i) {
					std::cout << ((pipeline::Move*)code)->End()(i) << " ";
				}
				std::cout << std::endl;
			}

			delete code;
		}
		});

	std::thread pause([&]() {
		while (1) {
			getchar();
			pipeline_pause(pipeline);
			getchar();
			pipeline_resume(pipeline);
		}
		});

	pipeline_wait_for_idle(pipeline);
	mcc.join();
	pipeline_delete(pipeline);
	gworker_delete(first);
}

int main()
{
	TestPipeline();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
