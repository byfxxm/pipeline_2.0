// test_main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cassert>
#include <thread>
#include "../pipeline/pipeline.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/pipeline.lib")
#else
#pragma comment(lib, "../Release/pipeline.lib")
#endif

#define WRITE(code) ((utils->worker->*utils->write)(code))

int main()
{
	auto pipeline = pipeline_create();

	auto first = [](Utils* utils, Code* code) {
		assert(!code);
		for (int i = 0; i < 10000; ++i) {
			WRITE(new Code{ i });
		}
	};
	auto procedure = [](Utils* utils, Code* code) {
		WRITE(new Code(*code));
		WRITE(code);
	};
	auto last = [](Utils* utils, Code* code) {
		std::cout << code->value << std::endl;
		delete code;
	};

	pipeline_add_procedure(pipeline, first);
	pipeline_add_procedure(pipeline, procedure);
	pipeline_add_procedure(pipeline, procedure);
	pipeline_add_procedure(pipeline, procedure);
	pipeline_add_procedure(pipeline, procedure);
	pipeline_add_procedure(pipeline, procedure);
	pipeline_add_procedure(pipeline, last);
	pipeline_start_async(pipeline);

	std::thread th([&]() {
		getchar();
		pipeline_stop_async(pipeline);
		});
	th.detach();

	pipeline_wait_for_idle(pipeline);
	pipeline_delete(pipeline);

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
