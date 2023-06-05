# `HappyHTTP` 사용법

- GitHub : https://github.com/mingodad/HappyHTTP
- 예제 코드 : `../ExampleCodes/HappyHTTP`

- Windows, Linux 지원  
- 사용하기 쉬움.

## 설치 방법

[GitHub](https://github.com/mingodad/HappyHTTP)에서 `happyhttp.cpp`와 `happyhttp.h`를 다운 받아 프로젝트 폴더에 포함한다.



## JSON GET Request

```cpp
void SendGetRequestJson()
{
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

    // 서버와 연결 및 콜백 함수 등록
	happyhttp::Connection conn("127.0.0.1", 11502);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

    // 요청 패킷 송신
	conn.request(
        "GET",                          // Method
		"/AuthCheck",                   // URI
		header, 
		(const unsigned char*)body,
		strlen(body)                    // Body Length
	);

    // 응답 대기
	while (conn.outstanding() == true)
	{
		conn.pump();
	}
}
```

## JSON POST Request

```cpp
void SendPOSTRequestJson()
{
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

    // 서버와 연결 및 콜백 함수 등록
	happyhttp::Connection conn("127.0.0.1", 11502);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

    // 요청 패킷 송신
	conn.request(
        "POST",                         // Method
		"/AuthCheck",                   // URI
		header,                         
		(const unsigned char*)body,
		strlen(body)                    // Body Length
	);

    // 응답 대기
	while (conn.outstanding() == true)
	{
		conn.pump();
	}
}
```