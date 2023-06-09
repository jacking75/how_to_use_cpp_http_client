#include <string>
#include <iostream>
#include <cstring>

#include "curl/curl.h"
#include "curlite.hpp"

const bool ExampleMethodGet()
{
	return true;
}

const bool ExampleMethodPost()
{
	return true;
}

const bool DoJsonRequest(
	const char* url, 
	const char* body_data, 
	const bool isPostMethod = false,
	const bool isSSL = false)
{
	curl_slist* header = nullptr;
	header = curl_slist_append(header, "Content-Type: application/json");
	const int32_t body_data_len = (int32_t)strlen(body_data);

	try
	{
		curlite::Easy easy;
		easy.set(CURLOPT_URL, url);
		easy.set(CURLOPT_POST, 1L);
		easy.set(CURLOPT_SSL_VERIFYPEER, 1L);
		easy.set(CURLOPT_SSL_VERIFYHOST, 1L);
		easy.set(CURLOPT_HTTPHEADER, header);
		easy.set(CURLOPT_POSTFIELDS, body_data);
		easy.set(CURLOPT_POSTFIELDSIZE, body_data_len);
		easy.set(CURLOPT_FOLLOWLOCATION, true);

		std::cout << easy << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Got an exception: " << e.what() << std::endl;
	}


	return true;
}

int main()
{
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
	DoJsonRequest(auth_check_url, auth_check_body_data, true);
	DoJsonRequest(inapp_check_url, inapp_check_body_data, true);

	return 0;
}