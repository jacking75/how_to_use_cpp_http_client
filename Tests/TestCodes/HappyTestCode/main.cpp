#pragma comment(lib, "ws2_32")

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <thread>
#include "happyhttp.h"

namespace testset
{
	uint32_t tps = 0;
	uint64_t complete_count = 0;
	bool running;

	void OnBegin(const happyhttp::Response* response, void* userData)
	{
	}

	void OnData(const happyhttp::Response* response, void* userData, const unsigned char* responseData, int responseDataLength)
	{
	}

	void OnComplete(const happyhttp::Response* response, void* userData)
	{
	}

	void SendRequest(const char* host, const char* url, const int port, const char body[], const int32_t body_size)
	{
		const char* header[] = {
			"Connection", "close",
			0
		};

		happyhttp::Connection conn(host, port);

		conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

		conn.request(
			"POST",
			url,
			header,
			(const unsigned char*)body,
			body_size
		);

		while (conn.outstanding() == true)
		{
			conn.pump();
		}

		conn.close();
	}

	void Worker(const uint32_t body_size)
	{
		const char* host = "127.0.0.1";
		const char* uri = "/AuthCheck";
		const int32_t port = 11502;
		char* p_body = new char[body_size];

		while (running == true)
		{
			SendRequest(host, uri, port, p_body, body_size);

			InterlockedIncrement(&tps);

			Sleep(1);
		}

		delete[] p_body;
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
		WSAData wsaData;
		int code = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (code != 0)
		{
			std::cout << "WSAStartup failed with error: " << code << std::endl;
			return;
		}

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

		WSACleanup();
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