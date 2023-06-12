#include <iostream>
#include "httplib.h"

namespace examples
{
	void SimpleRequest()
	{
		httplib::Client connection("example.com", 80);
		httplib::Result result = connection.Post("/");

		if (result == nullptr)
		{
			std::cout << "error code: " << result.error() << std::endl;
			return;
		}

		std::cout << result->status << std::endl;
		std::cout << result->body << std::endl;
	}

	void SendJsonRequest(const std::string& host, const int port, const std::string& path, const char* body) 
	{
		httplib::Headers headers = {
			{"Content-Type", "application/json"}
		};

		httplib::Client connection(host, port);
		httplib::Result result = connection.Post(path, headers, body, "application/json");

		if (result == nullptr)
		{
			std::cout << "error code: " << result.error() << std::endl;
			return;
		}

		std::cout << result->status << std::endl;
		std::cout << result->body << std::endl;
	}
}

int main() 
{
	const auto auth_check_body = R"(
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

	examples::SimpleRequest();
	examples::SendJsonRequest("127.0.0.1", 11502, "/AuthCheck", auth_check_body);
	examples::SendJsonRequest("127.0.0.1", 11502, "/InAppCheck", inapp_check_body_data);

	return 0;
}







| | AuthID | AuthToken  |
| | -- | -- |
| | `test01` | `DUWPQCFN5DQF4P` |
| | `test02` | `DYG5R07M7RUV07` |
| | `test03` | `5GZF7OFY05P4TT` |
| | `test04` | `94ILRSD4LRXE6N` |
| | `test05` | `GPKJ442KR1BK0U` |
| | `test06` | `P2H95LNF6NT8UC` |
| | `test07` | `JXOU845OYZJUXG` |
| | `test08` | `N21SK6AXKQWS5B` |
| | `test09` | `X7S4WCTKMY6YVK` |
| | `test10` | `HIB0KU1A6FGVT1` |
| | `test11` | `0HM20Q8A4GFCBX` |
| | `test12` | `9IPHAAF6P88BMP` |
| | `test13` | `D58RFSAAAP1RWG` |
| | `test14` | `MYQOR56M574OIG` |
| | `test15` | `M0A7BOS0CVVN5L` |
| | `test16` | `0KJLTAMCVQBRLX` |
| | `test17` | `1E4XH0PL1XRGI8` |
| | `test18` | `FK4K9SYSB63L7R` |