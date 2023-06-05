#include <cstdio>
#include <cstring>

#ifdef _WIN32
#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <ws2tcpip.h>
#endif

#include "happyhttp.h"

int count = 0;

void OnBegin(const happyhttp::Response* r, void* userdata)
{
	printf("BEGIN (%d %s)\n", r->getstatus(), r->getreason());
	count = 0;
}

void OnData(const happyhttp::Response* r, void* userdata, const unsigned char* data, int n)
{
	fwrite(data, 1, n, stdout);
	count += n;
}

void OnComplete(const happyhttp::Response* r, void* userdata)
{
	printf("COMPLETE (%d bytes)\n", count);
}

void Test1()
{
	puts("-----------------Test1------------------------");

	// simple simple GET
	happyhttp::Connection conn("127.0.0.1", 11502);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.request("GET", "/happyhttp/test.php", 0, 0, 0);

	while (conn.outstanding())
	{
		conn.pump();
	}
}

void Test2()
{
	puts("-----------------Test2------------------------");
	// POST using high-level request interface

	const char* headers[] =
	{
		"Connection", "close",
		"Content-type", "application/x-www-form-urlencoded",
		"Accept", "text/plain",
		0
	};

	const char* body = "answer=42&name=Bubba";

	happyhttp::Connection conn("scumways.com", 80);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.request(
		"POST",
		"/happyhttp/test.php",
		headers,
		(const unsigned char*)body,
		(int)strlen(body)
	);

	while (conn.outstanding())
	{
		conn.pump();
	}
}

void Test3()
{
	puts("-----------------Test3------------------------");

	// POST example using lower-level interface

	const char* params = "answer=42&foo=bar";
	auto len = (int)strlen(params);

	happyhttp::Connection conn("scumways.com", 80);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.putrequest("POST", "/happyhttp/test.php");
	conn.putheader("Connection", "close");
	conn.putheader("Content-Length", len);
	conn.putheader("Content-type", "application/x-www-form-urlencoded");
	conn.putheader("Accept", "text/plain");
	conn.endheaders();
	conn.send((const unsigned char*)params, len);

	while (conn.outstanding())
	{
		conn.pump();
	}
}

void Test4()
{
	puts("-----------------Test4------------------------");

	// JSON POST example

	const char* header[] = {
		"Connection", "close",
		"Content-type", "application/json",
		"Accept", "text/plain",
		0
	};

	auto body = R"(
		{
			"AuthID":"cov1013@com2us.com",
			"AuthToken":"Test"
		}
	)";

	happyhttp::Connection conn("127.0.0.1", 11502);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.request(
		"POST",
		"/AuthCheck",
		header,
		(const unsigned char*)body,
		strlen(body)
	);

	while (conn.outstanding() == true)
	{
		conn.pump();
	}
}

void Test5()
{
	puts("-----------------Test4------------------------");

	// JSON GET example

	const char* header[] = {
		"Connection", "close",
		"Content-type", "application/json",
		"Accept", "text/plain",
		0
	};

	auto body = R"(
		{
			"AuthID":"cov1013@com2us.com",
			"AuthToken":"Test"
		}
	)";

	happyhttp::Connection conn("127.0.0.1", 11502);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.request(
		"GET",
		"/AuthCheck",
		header,
		(const unsigned char*)body,
		strlen(body)
	);

	while (conn.outstanding() == true)
	{
		conn.pump();
	}
}

int main()
{
#ifdef _WIN32
	WSAData wsaData;
	int code = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (code != 0)
	{
		fprintf(stderr, "shite. %d\n", code);
		return 0;
	}
#endif //_WIN32

	try
	{
		//Test1();
		//Test2();
		//Test3();
		Test4();
	}
	catch (happyhttp::Wobbly& e)
	{
		fprintf(stderr, "Exception:\n%s\n", e.what());
	}

#ifdef _WIN32
	WSACleanup();
#endif // _WIN32

	return 0;
}