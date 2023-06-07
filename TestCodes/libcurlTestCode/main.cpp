#pragma comment(lib, "winmm")

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <string>
#include <iostream>
#include <cstring>
#include <curl/curl.h>
#include <vector>
#include <thread>

namespace testset
{
	uint32_t tps = 0;
	uint64_t complete_count = 0;
	bool running;

	size_t OnResponse(char* ptr, size_t size, size_t nmemb, std::string* stream)
	{
		return size * nmemb;
	}

	void SendRequest(const std::string& URL, const std::string& body)
	{
		CURL* curl;
		curl = curl_easy_init();

		if (curl == NULL)
		{
			printf("Failed intialize curl instance");
			return;
		}

		CURLcode res;

		// Header ¼¼ÆÃ
		curl_slist* header = NULL;
		header = curl_slist_append(header, "Connection: Close");
		header = curl_slist_append(header, "Accept: text/plain");
		header = curl_slist_append(header, "Content-Type: application/json");

		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnResponse);

		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		curl_slist_free_all(header);

		if (res != CURLE_OK)
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
	}

	void Worker(const uint32_t body_size)
	{
		std::string url = "http://127.0.0.1:11502/AuthCheck";

		char* body = new char[body_size];

		while (running == true)
		{
			SendRequest(url, body);

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