#include <iostream>
#include "wnetwrap.h"

void SimpleGet()
{
	wrap::Response r;
	r = wrap::HttpsRequest(wrap::Url{ "https://www.postman-echo.com/get" },
		wrap::Header{ {"Referer", "www.bla.com"}, { "Content-Type","*/*" } },
		wrap::Parameters{ {"fruit", "mango"}, { "price","£3" } }
	);

	std::cout << std::endl << r.text << std::endl;
}

void PostJson()
{
	wrap::Response r = wrap::HttpsRequest(
		wrap::Url{ "http://127.0.0.1:11502/AuthCheck" },
		wrap::Header{
			{"Connection", "close"},
			{ "Content-type", "application/json" },
			{ "Accept", "text/plain" }
	},
		wrap::Body{ R"(
			{
				"AuthID":"cov1013@com2us.com",
				"AuthToken":"Test"
			}
		)" },
		wrap::Method{ "POST" });
	std::cout << r.text << std::endl;
}

int main()
{
	PostJson();

	SimpleGet();

	system("PAUSE");
	return 0;
}