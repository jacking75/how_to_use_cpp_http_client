#include <string>
#include <iostream>
#include <cstring>

#include "curl/curl.h"
#include "curlcpp/curl_easy.h"

const bool DoJsonRequest(
	const char* url, 
	const char* body_data, 
	const bool isPostMethod = false,
	const bool isSSL = false)
{
	curl::curl_easy easy;
	curl_slist* header = nullptr;
	header = curl_slist_append(header, "Content-Type: application/json");

	const auto body_data_len = strlen(body_data);

	easy.add<CURLOPT_URL>(url);
	easy.add<CURLOPT_POST>(isPostMethod);
	easy.add<CURLOPT_HTTPHEADER>(header);
	easy.add<CURLOPT_SSL_VERIFYPEER>(isSSL);
	easy.add<CURLOPT_SSL_VERIFYHOST>(isSSL);
	easy.add<CURLOPT_POSTFIELDS>(body_data);
	easy.add<CURLOPT_POSTFIELDSIZE>(body_data_len);

	try {
		easy.perform();
	}
	catch (curl::curl_easy_exception& error) {
		std::cerr << error.what() << std::endl;
		return false;
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