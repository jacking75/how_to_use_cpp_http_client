#include <string>
#include <iostream>
#include <cstring>

#include "curl/curl.h"
#include "curly.hpp"

namespace examples
{
	// ������ ��û
	void SimpleRequest()
	{
		auto request = curly_hpp::request_builder()
			.method(curly_hpp::http_method::GET)
			.url("http://example.com")
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

	// JSON ��/����
	void SendRequestJson(const char* url, const char* body, const curly_hpp::http_method method)
	{
		// ��� ����
		curly_hpp::header_ilist_t headers = {
			{"Content-Type", "application/json"}
		};

		// ��û ���� ���� �� �ٷ� �۽�
		auto request = curly_hpp::request_builder()
			.method(method)
			.url(url)
			.headers(headers)
			.content(body)
			.send();

		// ���� ��� (���ο��� ���� ������ ���ɰ� �����Ѵ�.)
		request.wait();

		// ���� ó�� (���ο��� ���� ������ ���ɰ� �����Ѵ�. ��, ���� ȹ���ߴٴ� �� ���� �����͸� �޾Ҵٴ� ���̴�.)
		if (request.is_done())
		{
			// ���� �����͸� �����´�.
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
}

int main()
{
	// �۽� ��� �ν��Ͻ� ����
	curly_hpp::performer performer;

	const char* auth_check_url = "http://127.0.0.1:11502/AuthCheck";
	const char* inapp_check_url = "http://127.0.0.1:11502/InAppCheck";
	const auto auth_check_body_data = R"(
		{
			"AuthID":"test01",
			"AuthToken":"DUWPQCFN5DQF4P"
		}
	)";

	const auto inapp_check_body_data = R"(
		{
			"Receipt":"WkuOATWDQ909OET9cBjVEXEgI3KqTTbThNFe206bywlkSBiUD1hgrCltj3g1a84d"
		}
	)";

	examples::SendRequestJson(auth_check_url, auth_check_body_data, curly_hpp::http_method::POST);
	examples::SendRequestJson(inapp_check_url, inapp_check_body_data, curly_hpp::http_method::POST);

	return 0;
}