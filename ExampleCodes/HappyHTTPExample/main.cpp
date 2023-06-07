
#pragma comment(lib, "ws2_32")
#include <cstdio>
#include <cstring>
#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include "happyhttp.h"

int count = 0;

void OnBegin(const happyhttp::Response* response, void* userData)
{
	printf("BEGIN (%d %s)\n", response->getstatus(), response->getreason());

	count = 0;
}

void OnData(const happyhttp::Response* response, void* userData, const unsigned char* responseData, int responseDataLength)
{
	fwrite(responseData, 1, responseDataLength, stdout);

	count += responseDataLength;
}

void OnComplete(const happyhttp::Response* response, void* userData)
{
	printf("\nCOMPLETE (%d bytes)\n", count);
}

void SendRequestMethodGet()
{
	happyhttp::Connection conn("www.postman-echo.com", 80);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	const char* body = "fruit=mango&price=3";

	conn.request(
		"GET",
		"/get",
		NULL,
		(const unsigned char*)body,
		(int)strlen(body)
	);

	while (conn.outstanding())
	{
		conn.pump();
	}
}

void SendRequestMethodPost()
{
	const char* headers[] =
	{
		"Connection", "close",
		"Content-type", "application/x-www-form-urlencoded",
		"Accept", "text/plain",
		0
	};

	const char* body = "fruit=mango&price=3";

	happyhttp::Connection conn("www.postman-echo.com", 80);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.request(
		"POST",
		"/post",
		headers,
		(const unsigned char*)body,
		(int)strlen(body)
	);

	while (conn.outstanding())
	{
		conn.pump();
	}
}

void SendPostRequest_LowLevelInterface()
{
	const char* body = "fruit=mango&price=3";
	auto bodyLen = (int)strlen(body);

	happyhttp::Connection conn("www.postman-echo.com", 80);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.putheader("Connection", "close");
	conn.putheader("Content-Length", bodyLen);
	conn.putheader("Content-type", "application/x-www-form-urlencoded");
	conn.putheader("Accept", "text/plain");
	conn.endheaders();

	conn.putrequest("POST", "/post");
	conn.send((const unsigned char*)body, bodyLen);

	while (conn.outstanding())
	{
		conn.pump();
	}
}

void SendJsonRequestMethodGet(const std::string& host, const std::string& uri, const int port, const std::string body)
{
	const char* header[] = {
		"Connection", "close",
		"Content-type", "application/json",
		"Accept", "text/plain",
		0
	};

	happyhttp::Connection conn(host.c_str(), port);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.request(
		"GET",
		uri.c_str(),
		header,
		(const unsigned char*)body.c_str(),
		strlen(body.c_str())
	);

	while (conn.outstanding() == true)
	{
		conn.pump();
	}
}

void SendJsonRequestMethodPost(const std::string& host, const std::string& uri, const int port, const std::string body)
{
	const char* header[] = {
		"Connection", "close",
		"Content-type", "application/json",
		"Accept", "text/plain",
		0
	};

	happyhttp::Connection conn(host.c_str(), port);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.request(
		"POST",
		uri.c_str(),
		header,
		(const unsigned char*)body.c_str(),
		strlen(body.c_str())
	);

	while (conn.outstanding() == true)
	{
		conn.pump();
	}
}

int main()
{
	WSAData wsaData;
	int code = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (code != 0)
	{
		std::cout << "WSAStartup failed with error: " << code << std::endl;
		return 0;
	}

	const std::string SERVER_HOST = "127.0.0.1";
	const int SERVER_PORT = 11502;

	try
	{
		// Postman Echo Test
		SendRequestMethodGet();
		SendRequestMethodPost();

		// FakerHiveServer AuthCheck Test
		std::string authCheckReqData = R"(
			{
				"AuthID":"test01",
				"AuthToken":"DUWPQCFN5DQF4P"
			}
		)";
		SendJsonRequestMethodGet(SERVER_HOST, "/AuthCheck", SERVER_PORT, authCheckReqData);
		SendJsonRequestMethodPost(SERVER_HOST, "/AuthCheck", SERVER_PORT, authCheckReqData);

		// FakerHiveServer InAppCheck Test
		std::string inAppCheckReqData = R"(
			{
				"Receipt":"WkuOATWDQ909OET9cBjVEXEgI3KqTTbThNFe206bywlkSBiUD1hgrCltj3g1a84d"
			}
		)";
		SendJsonRequestMethodPost(SERVER_HOST, "/InAppCheck", SERVER_PORT, inAppCheckReqData);
	}
	catch (happyhttp::Wobbly& e)
	{
		fprintf(stderr, "Exception:\n%s\n", e.what());
	}

	WSACleanup();

	return 0;
}