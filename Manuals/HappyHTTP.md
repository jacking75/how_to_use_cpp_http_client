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

- 사용하기 간편하다. (*라이브러리 기능이 직관적이다.*)
- `Windows`와 `Linux`를 지원한다. (*해당 문서에서는 `Windows` 환경에서의 사용법만 다룬다.*)
- 응답 데이터를 콜백 함수(`OnBegin`, `OnData`, `OnComplete`)를 통해 핸들링한다.
- 별도의 라이브러리 설치 없이 **해당 라이브러리의 소스 코드만으로 사용 가능**하다.

## 라이브러리 사용하기

가장 먼저 `WSAStartup()` 함수를 호출하여 `WinSock`을 초기화를 해야한다.
```cpp
bool NetInit()
{
	WSAData wsaData;
	int32_t errcode = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (errcode != NO_ERROR)
	{
		std::cout << "WSAStartup failed with error: " << errcode << std::endl;
		return false;
	}
	return true;
}
```

이후 응답 데이터에 대한 각각의 콜백 함수를 선언 및 정의한다.

### `OnBegin`
- 응답 데이터 수신 시 **한 번 호출**된다.
- 매개 변수로 받은 `happyhttp::Response*`를 통해 응답 상태를 확인할 수 있다.

#### 예제 코드
```cpp
void OnBegin(const happyhttp::Response* response, void* userData)
{
	// 응답 상태를 출력한다.
	printf("BEGIN (%d %s)\n", response->getstatus(), response->getreason());
}
```

### `OnData`
- 응답 데이터 수신을 위한 **Folling 중 (*아래 설명*) 여러 번 호출**된다.
- 매개 변수로 받은 `happyhttp::Response*`를 통해 응답 상태를 확인할 수 있다.
- 매개 변수로 받은 `responseData`와 `responseDataLength`로 수신 받은 데이터에 접근 가능하다.

#### 예제 코드
```cpp
void OnData(const happyhttp::Response* response, void* userData, const unsigned char* responseData, int responseDataLength)
{
	// 표준 출력 장치에 현재 수신 받은 응답 데이터 출력
	fwrite(responseData, 1, responseDataLength, stdout);
}
```

### `OnComplete`
- 모든 응답 데이터를 수신했을 경우 **한 번 호출**된다.
- Folling이 종료된다.

#### 예제 코드
```cpp
void OnComplete(const happyhttp::Response* response, void* userData)
{
	std::cout << std::endl;
	std::cout << "Done response data receive" << std::endl;
}
```

### Folling 설명
- 요청 패킷 송신 후 응답 데이터를 수신 받기 위해 다음과 같이 `outstanding()` 함수와 `pump()` 함수를 통해 Folling한다.
```cpp
void ReceiveResponseData(happyhttp::Connection* p_conn)
{
	while (p_conn->outstanding())	// 응답 데이터가 남아있는가?
	{
		// 응답 데이터를 계속 수신한다.
		p_conn->pump();
	}
}
```

### 예제 1. METHOD : GET
```cpp
void ExampleMethodGet()
{
	const char* host = "www.postman-echo.com";
	const int32_t port = 80;
	const char* body_data = "fruit=mango&price=3";
	const int32_t body_data_len = (int32_t)strlen(body_data);

	// happyhttp 인스턴스 생성
	happyhttp::Connection conn(host, port);

	// 콜백 함수 등록
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	// 요청
	conn.request(
		"GET",
		"/get",
		NULL,
		(const unsigned char*)body_data,
		body_data_len
	);

	ReceiveResponseData(conn);
}
```

### 예제 2. METHOD : POST
```cpp
void ExampleMethodPost()
{
	const char* url = "www.postman-echo.com";
	const int32_t port = 80;
	
	const char* header[] =
	{
		"Connection", "close",
		"Content-type", "application/x-www-form-urlencoded",
		"Accept", "text/plain",
		0
	};
	const char* body_data = "fruit=mango&price=3";
	const int32_t body_data_len = (int)strlen(body_data);

	// happyhttp 인스턴스 생성
	happyhttp::Connection conn(url, port);

	// 콜백 함수 등록
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	// 요청
	conn.request(
		"POST",
		"/post",
		header,
		(const unsigned char*)body_data,
		body_data_len
	);

	ReceiveResponseData(conn);
}
```

### 예제 3. METHOD : POST (Low-Level Interface)
```cpp
void ExampleMethodPostLowLevelInterface()
{
	const char* url = "www.postman-echo.com";
	const int32_t port = 80;

	const char* body_data = "fruit=mango&price=3";
	const int32_t body_data_len = (int)strlen(body_data);

	// happyhttp 인스턴스 생성
	happyhttp::Connection conn(url, port);

	// 콜백 함수 등록
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	// 헤더 세팅
	conn.putheader("Connection", "close");
	conn.putheader("Content-type", "application/x-www-form-urlencoded");
	conn.putheader("Accept", "text/plain");
	conn.endheaders();

	// 메소드 세팅
	conn.putrequest("POST", "/post");

	// 송신
	conn.send((const unsigned char*)body_data, body_data_len);

	ReceiveResponseData(conn);
}
```

### 예제 4. JSON Request
- BodyData를 `JSON`으로 송신하고 싶은 경우 다음과 같이 사용할 수 있다.
```cpp
bool DoJsonRequest (
	const char* host, 
	const int32_t port, 
	const char* url, 
	const char* method, 
	const char* body_data)
{
	const int32_t body_data_len = strlen(body_data);

	if (body_data_len <= 0)
	{
		return false;
	}

	const char* header[] = {
		"Connection", "close",
		"Content-type", "application/json",	// JSON으로 설정한다.
		"Accept", "text/plain",
		0
	};

	happyhttp::Connection conn(host, port);
	conn.setcallbacks(OnBegin, OnData, OnComplete, 0);

	conn.request(
		method,
		url,
		header,
		(const unsigned char*)body_data,
		body_data_len
	);

	ReceiveResponseData(conn);

	return true;
}
```

#### 실제 사용 예시
```cpp
int main()
{
	if (NetInit() == false)
	{
		return 0;
	}

	const char* host = "127.0.0.1";
	const int32_t port = 11502;

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

	try
	{
		DoJsonRequest(host, port, "/AuthCheck", "GET", auth_check_body_data);
		DoJsonRequest(host, port, "/AuthCheck", "POST", auth_check_body_data);
		DoJsonRequest(host, port, "/InAppCheck", "POST", inapp_check_body_data);
	}
	catch (happyhttp::Wobbly& e)
	{
		std::cout << "happyhttp Exception: " << e.what() << std::endl;
	}

	WSACleanup();

	return 0;
}
```