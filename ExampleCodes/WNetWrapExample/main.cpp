#include <iostream>
#include "wnetwrap.h"

void SendRequestMethodGet()
{
	wrap::Response res = wrap::HttpsRequest(
		wrap::Url{ "https://www.postman-echo.com/get" },
		wrap::Parameters{{"fruit", "mango"}, { "price","£3" }}
	);

	std::cout << res.text << std::endl;
}

void SendRequestMethodPost()
{
	wrap::Response res = wrap::HttpsRequest(
		wrap::Url{ "https://www.postman-echo.com/post" },
		wrap::Method{ "POST" },
		wrap::Parameters{{"fruit", "mango"}, { "price","£3" }}
	);

	std::cout << res.text << std::endl;
}

void SendJsonRequestMethodGet(const std::string& URL, const std::string& body)
{
	wrap::Response res = wrap::HttpsRequest(
		wrap::Url{ URL },
		wrap::Header{{"Connection", "close"}, { "Content-type", "application/json" }, { "Accept", "text/plain" }},
		wrap::Body{body}
	);

	std::cout << res.text << std::endl;
}

void SendJsonRequestMethodPost(const std::string& URL, const std::string& body)
{
	wrap::Response res = wrap::HttpsRequest(
		wrap::Url{ URL },
		wrap::Header{{"Connection", "close"}, { "Content-type", "application/json" }, { "Accept", "text/plain" }},
		wrap::Method{ "POST" },
		wrap::Body{body}
	);

	std::cout << res.text << std::endl;
}

int main()
{

	// Postman Echo Test
	SendRequestMethodGet();
	SendRequestMethodPost();


	// FakerHiveServer AuthCheck Test
	const std::string AUTH_CHECK_SERVER_URL = "http://127.0.0.1:11502/AuthCheck";
	std::string authCheckReqData = R"(
		{
			"AuthID":"cov1013@com2us.com",
			"AuthToken":"Test"
		}
	)";
	SendJsonRequestMethodGet(AUTH_CHECK_SERVER_URL, authCheckReqData);
	SendJsonRequestMethodPost(AUTH_CHECK_SERVER_URL, authCheckReqData);


	// FakerHiveServer InAppCheck Test
	const std::string INAPP_CHECK_SERVER_URL = "http://127.0.0.1:11502/InAppCheck";
	std::string inAppCheckReqData = R"(
		{
			"Receipt":"WkuOATWDQ909OET9cBjVEXEgI3KqTTbThNFe206bywlkSBiUD1hgrCltj3g1a84d"
		}
	)";
	SendJsonRequestMethodPost(INAPP_CHECK_SERVER_URL, inAppCheckReqData);

	return 0;
}