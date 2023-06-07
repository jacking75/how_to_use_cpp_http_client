#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <thread>
#include <iostream>
#include <windows.h>
#include "wnetwrap.h"

namespace testset
{
	uint32_t tps = 0;
	uint64_t complete_count = 0;
	SRWLOCK srw_obj;
	bool running;

	void SendRequest(const std::string& URL, const std::string& body)
	{
		wrap::Response res = wrap::HttpsRequest(
			wrap::Url{ URL },
			wrap::Header{{"Connection", "close"}, { "Content-type", "application/json" }, { "Accept", "text/plain" }},
			wrap::Method{ "POST" },
			wrap::Body{body}
		);
	}

	void Worker(const uint32_t body_size)
	{
		std::string url = "http://127.0.0.1:11502/AuthCheck";

		char* body = new char[body_size];

		while (running == true)
		{
			AcquireSRWLockExclusive(&srw_obj);

			SendRequest(url, body);

			ReleaseSRWLockExclusive(&srw_obj);

			InterlockedIncrement(&tps);

			Sleep(1);
		}

		delete[] body;
	}

	void Monitor(const uint32_t worker_count, const uint32_t test_time_sec)
	{
		std::cout << "Worker Count   : " << worker_count << std::endl;
		std::cout << "Test Time (sec): " << test_time_sec << std::endl;

		while (running == true)
		{
			Sleep(999);

			std::cout << "TPS: " << tps << std::endl;

			complete_count += tps;
			tps = 0;
		}
	}

	void Timer(int32_t sec)
	{
		Sleep(1000 * sec);

		running = false;
	}

	void InitAndTestRun(const uint32_t worker_count, const uint32_t test_time_sec, const uint32_t body_size)
	{
		InitializeSRWLock(&srw_obj);

		running = true;

		std::thread monitor(Monitor, worker_count, test_time_sec);

		std::vector<std::thread> workers;

		for (uint32_t i = 0; i < worker_count; i++)
		{
			workers.push_back(std::thread(Worker, body_size));
		}

		std::thread timer(Timer, test_time_sec);

		timer.join();

		monitor.join();

		auto iter = workers.begin();
		for (iter; iter != workers.end();)
		{
			iter->join();
			iter = workers.erase(iter);
		}
	}
}

int main(int argc, char* argv[])
{
	{
		auto worker_count = std::stoi(argv[1]);
		auto test_time_sec = std::stoi(argv[2]);
		auto body_size = std::stoi(argv[3]);

		testset::InitAndTestRun(worker_count, test_time_sec, body_size);

		std::cout << "TotalReqRes: " << testset::complete_count << std::endl;
	}

	_CrtDumpMemoryLeaks();

	return 0;
}