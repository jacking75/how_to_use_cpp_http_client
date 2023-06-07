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
	bool running;

	void SendRequest(const std::string& URL, const std::string& body)
	{
		wrap::Response res = wrap::HttpsRequest(
			wrap::Url{ URL },
			wrap::Header{
				{"Connection", "close"}, 
				{ "Content-type", "application/json" }, 
				{ "Accept", "text/plain" }
			},
			wrap::Method{ "POST" },
			wrap::Body{body}
		);
	}

	void Worker()
	{
		std::string url = "http://127.0.0.1:11502/AuthCheck";
		//std::string url = "http://127.0.0.1:11502/InAppCheck";

		const char* body = R"(
			{
				"AuthID":"test01",
				"AuthToken":"DUWPQCFN5DQF4P"
			}
		)";

		//const char* body = R"(
		//	{
		//		"Receipt":"aepIhSInxFk68yvdk66cwfskjti6sBKTqPBHo6vdI5J664EpOVBYN4lwqk89n1YJ"
		//	}
		//)";

		while (running == true)
		{
			SendRequest(url, body);

			InterlockedIncrement(&tps);

			Sleep(1);
		}
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

	void InitAndTestRun(const uint32_t worker_count, const uint32_t test_time_sec)
	{
		running = true;

		std::thread monitor(Monitor, worker_count, test_time_sec);

		std::vector<std::thread> workers;

		for (uint32_t i = 0; i < worker_count; i++)
		{
			workers.push_back(std::thread(Worker));
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

		testset::InitAndTestRun(worker_count, test_time_sec);

		std::cout << "TotalReqRes: " << testset::complete_count << std::endl;
	}

	_CrtDumpMemoryLeaks();

	return 0;
}