#include <string>
#include <iostream>
#include <cstring>

#include "curl/curl.h"
#include "swish/swish.h"

using namespace swish;

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
	// create a new HTTP client
	auto client = swish::Client();

	std::string_view data = body_data;

	// Perform request
	auto [response, status] = client.Post(url, data);
	
	// Check if any errors occured
	if (IsOK(status)) {
		// convert body buffer to std::basic_string<char> aka std::string
		std::cout << response.body.ToString() << "\n";

	}
	else {
		// Interpret status code to english
		std::cerr << "The following Error occured: " << InterpretStatusCode(status)
			<< "\n";
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