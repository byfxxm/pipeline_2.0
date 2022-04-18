// test_main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cassert>
#include <thread>
#include <chrono>
#include "ring_buffer.h"
#include "../pipeline/pipeline.h"
#include "../gparser_worker/gparser_worker.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/pipeline.lib")
#pragma comment(lib, "../Debug/gparser_worker.lib")
#else
#pragma comment(lib, "../Release/pipeline.lib")
#pragma comment(lib, "../Release/gparser_worker.lib")
#endif

class Fifo final :public OutputSwitch {
public:
	virtual void Write(Code* code) override {
		while (!ring_buffer_.Write(code))
			std::this_thread::yield();
	}

	void Read(Code*& code) {
		while (!ring_buffer_.Read(code))
			std::this_thread::yield();
	}

	bool IsEmpty() {
		return ring_buffer_.IsEmpty();
	}

private:
	RingBuffer<Code*, 1000> ring_buffer_;
};

class WorkerMiddle :public Worker {
public:
	virtual void Do(Code* code) override {
		Write(code);
	}
};

int main()
{
	auto pipeline = pipeline_create();
	auto gworker = gworker_create();
	gworker_load_file(gworker, "test1.nc");
	WorkerMiddle workers[10];

	pipeline_add_worker(pipeline, gworker);
	for (auto& worker : workers)
		pipeline_add_worker(pipeline, &worker);

	Fifo fifo;
	pipeline_set_output_switch(pipeline, &fifo);
	pipeline_start_async(pipeline);
	
	std::thread mcc([&]() {
		Code* code = nullptr;
		while (1) {
			fifo.Read(code);
			if (!code)
				break;
			std::cout << code->value << std::endl;
			delete code;
		}
		});

	std::thread th([&]() {
		getchar();
		pipeline_stop_async(pipeline);
		});
	th.detach();

	pipeline_wait_for_idle(pipeline);
	mcc.join();
	pipeline_delete(pipeline);
	gworker_delete(gworker);

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
