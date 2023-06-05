#include <iostream>

#include "wnetwrap.h"


void SimpleGet()
{
	wrap::Response r;
	r = wrap::HttpsRequest(wrap::Url{ "https://www.postman-echo.com/get" }, 
						wrap::Header{ {"Referer","www.bla.com"},{"Content-Type","*/*"} }, 
					wrap::Parameters{ {"fruit","mango"},{"price","£3"} }
			);
	
	std::cout << std::endl << r.text << std::endl;
}

void PostJson()
{	
	wrap::Response r = wrap::HttpsRequest(
		wrap::Url{ "http://127.0.0.1:11502/AuthCheck" },
		wrap::Header{
			{"Connection", "close"},
			{"Content-type", "application/json"},
			{"Accept", "text/plain"}
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

	//PostJson();
	/*
	cout << "status code: " + r.status_code << endl;
	cout << r.text << endl;
	cout << "received header:" << endl;
	cout << r.header["content-type"] << endl;

	cout << "sent headers map:" << endl;
	for (auto elem : r.sent_headers)
	{
		cout << elem.first + " : " + elem.second + "\r\n";
	}
*/
	//HttpsRequest(Url{ "https://archive-4.kali.org/kali-images/kali-2021.1/kali-linux-2021.1-live-amd64.iso" }, Download{});

	//wrap::Response r;
	//r = HttpsRequest(Url{ "www.postman-echo.com/get" }, Header{ {"Referer","www.bla.com"},{"Content-Type","*/*"} }, Parameters{ {"fruit","mango"},{"price","£3"} });
	//cout << endl << r.text << endl;

	//posting raw data - does not get url encoded
	//r = HttpsRequest(Url{ "www.postman-echo.com/post" }, Body{ "£" }, Method{ "POST" });
	//cout << endl << r.text << endl;
	//url form encode - key value pairs
	//r = wrap::HttpsRequest(wrap::Url{ "www.httpbin.org/post" }, wrap::Payload{ {"name","习近平"} }, wrap::Method{ "POST" }, wrap::Timeout{1000});
	//std::cout << std::endl << r.text << std::endl;



	//note: to upload to file.io do not use www in url, and always use filename file
	//r = HttpsRequest(Url{ "file.io" }, Multipart{ {"file:file","sample.txt"} }, Method{ "POST" });
	//cout << endl << r.text << endl;

	//r = wrap::HttpsRequest(wrap::Url{ "https://www.httpbin.org/basic-auth/user/passwd" }, wrap::Authentication{  "user","passwd"  });
	//std::cout << std::endl << r.text << std::endl;
	

	//receiving a cookie 
	/*r = wrap::HttpsRequest(Url{ "https://www.httpbin.org/cookies/set?cookie=yummy" });
	cout << endl << r.text << endl;
	cout << "status code: " + r.status_code << endl;
	cout << "redirect count: " << r.redirect_count << endl;
	cout << "rcd byte count: " << r.downloaded_bytes << endl;
	cout << "recd cookies map:" << endl;
	for (auto elem : r.cookies)
	{
		cout << elem.first + " : " + elem.second + "\r\n";
	}
	*/
	//sending a cookie with request
/*

	cout << "sent headers map:" << endl;
	for (auto elem : r.sent_headers)
	{
		cout << elem.first + " : " + elem.second + "\r\n";
	}

	cout << "recd headers map:" << endl;
	for (auto elem : r.header)
	{
		cout << elem.first + " : " + elem.second + "\r\n";
	}

	*/
	system("PAUSE");
	return 0;
}


