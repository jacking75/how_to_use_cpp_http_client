
#include <iostream>
#include "httplib.h"

int main() {

	httplib::Headers headers = { {"Content-Type", "application/json"} };
	std::string body = R"({"AuthID":"test01","AuthToken":"DUWPQCFN5DQF4P"})";
	httplib::Client cli("127.0.0.1", 11502);

	if (auto res = cli.Post("/AuthCheck", headers, body, "application/json"))
	{
		std::cout << res->status << std::endl;
		std::cout << res->get_header_value("Content-Type") << std::endl;
		std::cout << res->body << std::endl;
	}
	else 
	{
		std::cout << "error code: " << res.error() << std::endl;
	}

	return 0;
}