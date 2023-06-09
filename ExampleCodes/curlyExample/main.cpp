#include <string>
#include <iostream>
#include <cstring>
#include <curl/curl.h>
#include "curly.hpp"

curly_hpp::performer performer;

void ExampleMethodGet()
{
	auto request = curly_hpp::request_builder()
		.method(curly_hpp::http_method::GET)
		.url("http://www.httpbin.org/get")
		.send();

	request.wait();

	if (request.is_done()) 
	{
		auto response = request.take();
		std::cout << "Status code: " << response.http_code() << std::endl;
	}
	else 
	{
		std::cout << "Error message: " << request.get_error() << std::endl;
	}
}

void ExampleMethodPost()
{
	auto request = curly_hpp::request_builder()
		.method(curly_hpp::http_method::POST)
		.url("http://www.httpbin.org/post")
		.header("Content-Type", "application/json")
		.content(R"({"hello" : "world"})")
		.send();

	request.wait();

	if (request.is_done())
	{
		auto response = request.take();
		std::cout << "Status code: " << response.http_code() << std::endl;
	}
	else 
	{
		std::cout << "Error message: " << request.get_error() << std::endl;
	}
}

void DoJsonRequest(
	const char* url, 
	const char* body_data)
{
	auto request = curly_hpp::request_builder()
		.method(curly_hpp::http_method::POST)
		.url(url)
		.header("Content-Type", "application/json")
		.content(body_data)
		.send();

	request.wait();

	if (request.is_done())
	{
		auto response = request.take();
		std::cout << "Status code: " << response.http_code() << std::endl;
		std::cout << "Body content: " << response.content.as_string_view() << std::endl;
		std::cout << "Content Length: " << response.headers["content-length"] << std::endl << std::endl;
	}
	else
	{
		std::cout << "Error message: " << request.get_error() << std::endl;
	}
}

int main()
{
	ExampleMethodGet();
	ExampleMethodPost();

	const char* auth_check_url = "http://127.0.0.1:11502/AuthCheck";
	const char* inapp_check_url = "http://127.0.0.1:11502/InAppCheck";

	const auto auth_check_body_data =
		R"(
			{
				"AuthID":"test01",
				"AuthToken":"DUWPQCFN5DQF4P"
			}
		)";

	const auto inapp_check_body_data =
		R"(
			{
				"Receipt":"WkuOATWDQ909OET9cBjVEXEgI3KqTTbThNFe206bywlkSBiUD1hgrCltj3g1a84d"
			}
		)";

	DoJsonRequest(auth_check_url, auth_check_body_data);
	DoJsonRequest(inapp_check_url, inapp_check_body_data);

	return 0;
}