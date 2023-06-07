# `HappyHTTP` 사용법

예제 코드 : `~/ExampleCodes/HappyHTTPExample`

## 들어가기전에

해당 문서의 예제 코드(`~/ExampleCodes/HappyHTTPExample`)에서 사용되는 라이브러리 소스 코드는 원본 코드 빌드 시 발생하는 다양한 컴파일 오류와 에러 사항들을 수정한 코드이며, 실제 원본이 필요한 경우 [이곳](https://github.com/mingodad/HappyHTTP)을 참고한다.

## 라이브러리 설치하기

1. `~/ExampleCodes/HappyHTTPExample`에서 `happyhttp.cpp`와 `happyhttp.h`를 자신의 프로젝트 폴더 복사한다.

![install](../Images/HappyHTTP/install_01.png)

2. 소스 코드를 자신의 프로젝트에 포함시킨다. (*그림에서의 솔루션 이름이 `HappyHTTPExample`이지만, 실제로는 `HappyHTTP` 라이브러리를 사용하는 별도의 프로젝트라고 가정한다.*)

![install](../Images/HappyHTTP/install_02.png)

## 라이브러리 설명

- `Windows`와 `Linux`를 지원한다. (*해당 문서에서는 `Windows` 환경에서의 사용법만 다룬다.*)
- 응답 데이터를 콜백 함수(`OnBegin`, `OnData`, `OnComplete`)를 통해 핸들링 할 수 있다.
- 별도의 라이브러리 설치 없이, 해당 라이브러리의 소스 코드만으로 사용 가능하다.
- 요청 후 응답을 받기 위해 별도의 `while` 문을 사용하여 모든 응답 데이터를 수신받을 때 까지 `Folling` 해야한다.
```cpp
while (conn.outstanding())	// 모든 응답 데이터를 수신했는가?
{
	// 응답 데이터를 계속 수신한다.
	conn.pump();
}
```
- 라이브러리 사용전에 `WSAStartup()` 함수를 호출하여 `WinSock` 사용 초기화를 해야한다.
```cpp
WSAData wsaData;
int code = WSAStartup(MAKEWORD(2, 2), &wsaData);
if (code != 0)
{
	return 0;
}
```

## 예제코드

### OnBegin Example
- 응답 수신 시 한 번 호출
- 응답 상태 확인 가능.

```cpp
void OnBegin(const happyhttp::Response* response, void* userData)
{
	printf("BEGIN (%d %s)\n", response->getstatus(), response->getreason());
}
```

### OnData Example
- 응답 데이터 수신 시 여러 번 호출 (*모든 응답 데이터를 수신받을 때 까지 계속 호출된다.*)
```cpp
void OnData(const happyhttp::Response* response, void* userData, const unsigned char* responseData, int responseDataLength)
{
	fwrite(responseData, 1, responseDataLength, stdout);
}
```

### OnComplete Example
- 응답 데이터 수신 완료 시 한 번 호출
```cpp
void OnComplete(const happyhttp::Response* response, void* userData)
{
	printf("\nCOMPLETE\n";
}
```

### Get Request
```cpp
void SendRequestMethodGet()
{
	// 연결
	happyhttp::Connection conn("www.postman-echo.com", 80);

	// 콜백 함수 등록
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	const char* body = "fruit=mango&price=3";

	// 요청 패킷 송신
	conn.request(
		"GET",
		"/get",
		NULL,
		(const unsigned char*)body,
		(int)strlen(body)
	);

	// 응답 데이터 수신 처리 완료 대기
	while (conn.outstanding())
	{
		conn.pump();
	}
}
```

### POST Request
```cpp
void SendRequestMethodPost()
{
	// 헤더 설정
	const char* headers[] =
	{
		"Connection", "close",
		"Content-type", "application/x-www-form-urlencoded",
		"Accept", "text/plain",
		0
	};

	const char* body = "fruit=mango&price=3";

	// 연결
	happyhttp::Connection conn("www.postman-echo.com", 80);

	// 콜백 함수 등록
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	// 요청 패킷 송신
	conn.request(
		"POST",
		"/post",
		headers,
		(const unsigned char*)body,
		(int)strlen(body)
	);

	// 응답 데이터 수신 처리 완료 대기
	while (conn.outstanding())
	{
		conn.pump();
	}
}
```

### POST Request (Low-Level Interface)
```cpp
void SendPostRequest_LowLevelInterface()
{
	const char* body = "fruit=mango&price=3";
	auto bodyLen = (int)strlen(body);

	// 연결
	happyhttp::Connection conn("www.postman-echo.com", 80);

	// 헤더 설정
	conn.putheader("Connection", "close");
	conn.putheader("Content-Length", bodyLen);
	conn.putheader("Content-type", "application/x-www-form-urlencoded");
	conn.putheader("Accept", "text/plain");
	conn.endheaders();

	// 콜백 함수 등록
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	// 요청 방식 설정
	conn.putrequest("POST", "/post");

	// 송신
	conn.send((const unsigned char*)body, bodyLen);

	// 응답 데이터 수신 처리 완료 대기
	while (conn.outstanding())
	{
		conn.pump();
	}
}
```

### GET Request (JSON)
```cpp
void SendJsonRequestMethodGet(const std::string& host, const std::string& uri, const int port, const std::string body)
{
	// 헤더 설정
	const char* header[] = {
		"Connection", "close",
		"Content-type", "application/json",
		"Accept", "text/plain",
		0
	};

	// 연결
	happyhttp::Connection conn(host.c_str(), port);

	// 콜백 함수 등록
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	// 요청 패킷 송신
	conn.request(
		"GET",
		uri.c_str(),
		header,
		(const unsigned char*)body.c_str(),
		strlen(body.c_str())
	);

	// 응답 데이터 수신 처리 완료 대기
	while (conn.outstanding() == true)
	{
		conn.pump();
	}
}
```

### POST Request (JSON)
```cpp
void SendJsonRequestMethodPost(const std::string& host, const std::string& uri, const int port, const std::string body)
{
	// 헤더 세팅
	const char* header[] = {
		"Connection", "close",
		"Content-type", "application/json",
		"Accept", "text/plain",
		0
	};

	// 연결
	happyhttp::Connection conn(host.c_str(), port);

	// 콜백 함수 등록
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	// 요청 패킷 송신
	conn.request(
		"POST",
		uri.c_str(),
		header,
		(const unsigned char*)body.c_str(),
		strlen(body.c_str())
	);


	// 응답 데이터 수신 처리 완료 대기
	while (conn.outstanding() == true)
	{
		conn.pump();
	}
}
```

### 사용하는 부분
```cpp
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

#ifdef _WIN32
	WSACleanup();
#endif // _WIN32
}
```