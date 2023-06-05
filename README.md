# C++에서 http 요청하는 방법
- C++ 이후에 나온 언어들은 인터넷 시대에 나와서 대부분 표준 라이브러리에서 http 통신 기능을 지원하고 있다.  
- 그러나 C++는 아직까지 표준 라이브러리에서 http 통신을 지원하지 않아서 http 요청을 할 때 타 언어에 비해서 불편하다.  
- 해당 문서에서는 `Win32 API`, 외부 라이브러리를 사용하여 http 요청하는 방법에 대해 설명한다.



<br>      


    
# 테스트용 서버

코드 경로 : `./FakeHiveServer`

## 서버 설명

- `ASP.NET Core(.NET 7)`를 사용.
- `http` 요청에 응답을 반환하는 더미용 서버.
- 2개의 `POST`용 `API`와 1개의 `GET`용 `API`가 존재.
- 패킷 Body 포맷은 `JSON`을 사용.

## 요청 패킷 예제
```shell
# POST AuthCheck
POST http://localhost:11502/AuthCheck
Content-Type: application/json

{
  "AuthID":"test03",
  "AuthToken":"5GZF7OFY05P4TT"
}

# GET AuthCheck
GET http://localhost:11502/AuthCheck
Content-Type: application/json

{
  "AuthID":"test03",
  "AuthToken":"5GZF7OFY05P4TT"
}

# POST CreateAccount
POST http://localhost:11500/CreateAccount
Content-Type: application/json

{
  "ID":"jacking751",
  "PW":"123qwe",
  "NickName": "com2us"
}
```  

### 패킷 작성 시 참고 사항

- `AuthCheck` 요청에 사용할 수 있는 `AuthID` 목록은 `FakeHiveServer\Controllers\AuthCheckController.cs`의 `void Init()` 함수를 참고한다.
- `CreateAccount` 요청에 사용할 수 있는 것은 `AuthToken` 목록은 `FakeHiveServer\Controllers\InAppCheckController.cs`의 `void Init()` 함수를 참고한다.
	  


<br>      
  

  
# 외부 라이브러리 소개
  
## [HappyHTTP](./Manuals/HappyHTTP.md)

## [WNetWrap](./Manuals/WNetWrap.md)

## [libcurl](./Manuals/libcurl.md)

## curlcpp (`libcurl` 설치 필요)
- `libcurl`의 **C++ 버전**
- [GitHub](https://github.com/JosephP91/curlcpp )  
- [공식사이트](https://josephp91.github.io/curlcpp  )

## curly.hpp (`libcurl` 설치 필요)
- [공식 사이트](http://matov.me/curly.hpp/ )
- Simple cURL C++17 wrapper  
- Asynchronous requests
- **C++ 17 이상**
  
### 예제코드
```cpp
auto request = net::request_builder()
    .method(net::http_method::POST)
    .url("http://www.httpbin.org/post")
    .header("Content-Type", "application/json")
    .content(R"({"hello" : "world"})")
    .send();

auto response = request.take();
std::cout << "Body content: " << response.content.as_string_view() << std::endl;
std::cout << "Content Length: " << response.headers["content-length"] << std::endl;
```

## Curlite (`libcurl` 설치 필요)
- [GitHub](https://github.com/grynko/curlite )  
- 사용하기 쉽다
- **C++ 11 이상**

## Swish (`libcurl` 설치 필요)
- [GitHub](https://github.com/lamarrr/swish )    
- **C++ 17 이상**
  
## malloy (`boost` 설치 필요) 
- [GitHub](https://github.com/tectu/malloy )
- Malloy is a small, embeddable HTTP & WebSocket server & client built on top of boost.
- Windows (with both MSVC and MinGW), Linux (Ubuntu, Debian, Fedora, ...), MacOS, FreeBSD
   
## EasyHttp (`POCO` 설치 필요) 
- [GitHub](https://github.com/sony/easyhttpcpp )
- A cross-platform HTTP client library with a focus on usability and speed.
  
## Httplib (cpp-httplib) 
- A C++11 single-file header-only cross platform HTTP/HTTPS library
- This library uses **'blocking'** socket I/O
  
- [GitHub](https://github.com/yhirose/cpp-httplib)
	- [Sample](https://cdecl.github.io/dev/cpp-httplib-sample/ )
	- [cpp-httplib + nlohmann.json를 사용하여 http 요청하기](https://docs.google.com/document/d/e/2PACX-1vTpb2n7xjHJAR0g8JEEI0BzDgzZAJkfEVTUJs5NL-yogwRGqs_nRNml99DQohaUdOxjhy1ffjaWzLtR/pub )  
    	- [nlohmann.json](https://github.com/nlohmann/json )