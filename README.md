# `C++`로 `HTTP` 통신하기
- `C++` 이후에 나온 언어들은 대부분 표준 라이브러리에서 `HTTP` 통신 기능을 지원하고 있다. 
- 그러나 `C++`는 아직 표준 라이브러리에서 `HTTP` 통신 기능을 지원하지 않기 때문에, 다른 언어에 비해 `HTTP` 사용이 불편하다.
- 이런 불편함을 타개하기 위해 `C++`로 제작된 다양한 `HTTP` 통신용 라이브러리가 등장했으며, 해당 문서에서는 이러한 라이브러리들의 소개와 설치 방법 및 간단한 사용법에 대해 설명한다.

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

# POST InAppCheckController
POST http://localhost:11500/InAppCheckController
Content-Type: application/json

{
  "Receipt":"XbRd1nN5ct0IKWNHiULeuxhnLOfhuqHs5vOvRCKVPh0cSQrZk9Dy8q6atVkY3Bg6",
}
```  

### `AuthCheck` 패킷 작성 시 참고 사항

- `AuthCheck` 요청에 사용할 수 있는 `AuthID`와 `AuthToken` 목록은 다음과 같다.
- 코드 경로 : `./FakerHiveServer/Controller/AuthCheckController.cs`
```CSharp
void Init()
{
	authUserData.Add("test01", "DUWPQCFN5DQF4P");
	authUserData.Add("test02", "DYG5R07M7RUV07");
	authUserData.Add("test03", "5GZF7OFY05P4TT");
	authUserData.Add("test04", "94ILRSD4LRXE6N");
	authUserData.Add("test05", "GPKJ442KR1BK0U");
	authUserData.Add("test06", "P2H95LNF6NT8UC");
	authUserData.Add("test07", "JXOU845OYZJUXG");
	authUserData.Add("test08", "N21SK6AXKQWS5B");
	authUserData.Add("test09", "X7S4WCTKMY6YVK");
	authUserData.Add("test10", "HIB0KU1A6FGVT1");
	authUserData.Add("test11", "0HM20Q8A4GFCBX");
	authUserData.Add("test12", "9IPHAAF6P88BMP");
	authUserData.Add("test13", "D58RFSAAAP1RWG");
	authUserData.Add("test14", "MYQOR56M574OIG");
	authUserData.Add("test15", "M0A7BOS0CVVN5L");
	authUserData.Add("test16", "0KJLTAMCVQBRLX");
	authUserData.Add("test17", "1E4XH0PL1XRGI8");
	authUserData.Add("test18", "FK4K9SYSB63L7R");
}
```

### `InAppCheckController` 패킷 작성 시 참고 사항

- `InAppCheckController` 요청에 사용할 수 있는 것은 `Receipt` 목록은 다음과 같다.
- 코드 경로 : `./FakerHiveServer/Controller/InAppCheckController.cs`
```CSharp
void Init()
{
	_receiptList.Add("QKsM2oPCeUiLWlwpTqXN5fIr4w0I7gMEB73573W8hGIn0WU9bQjNnxA7nQxhcvMP");
	_receiptList.Add("WkuOATWDQ909OET9cBjVEXEgI3KqTTbThNFe206bywlkSBiUD1hgrCltj3g1a84d");
	_receiptList.Add("1OjwHKctOp29VE1KLK75BbXYxKpTHufOOAwcCWo32xFAvthQdyX2UaOECIxIl802");
	_receiptList.Add("NuIDV687iXasG5wFuTQbtpiAHBVbAjwfpI5dMUHfw76PBipS7cheFc0SksK6R2Gn");
	_receiptList.Add("FSrhNe0gbFAKjjY7ZN6FPK1ImWHsQrsyMnyWqR14JntyLofloticXJ7oFVUpSLBd");
	_receiptList.Add("KEUqnainhuHKThpCxXnT7vGr0tMQ6IEL3pu764kkGUNTtdhAxcT2umID0LmVNi7K");
	_receiptList.Add("Cmu2JCJsVndrsCpFMg520SAY9nrwVSSFIQor4FXJpaRk4VXpNtsNwa2Yc9gIbLuH");
	_receiptList.Add("7IJi2nTCMVZ5HbE3KF8cUJ73Uw7f84aQhMMatjf21ZxajeBMffQePfN89uROSB5n");
	_receiptList.Add("gXIoGpNMkWcO74FQPlSNvUhUqmGp7kXvh5bZHCJCDr7ePXfkyyJTrwFBGYO5qr8b");
	_receiptList.Add("wglqUxLmKZjr3L6xUwrOT0ijNKqFY9PwDA4f143vUKB6rP4Sd1iScPakuRP0LMF2");
	_receiptList.Add("AFwoseSvylxeyhvssAtLKRUBrq71wXgW5Lrp62IOPYon8U1sNJGC5iMuLpt8yWPZ");
	_receiptList.Add("XbRd1nN5ct0IKWNHiULeuxhnLOfhuqHs5vOvRCKVPh0cSQrZk9Dy8q6atVkY3Bg6");
	_receiptList.Add("lOkJrV8drexk1aAsLrphZijejTYruYGnjXe0G6r27iJiKhJxFTi1Hc3RYhQ5m7hq");
	_receiptList.Add("dk8IbTxH1Kgn9GFqA8VV0EqEDFUI2P5aXAEmf2nhMJsmNO86IgLSwVgNEGpXHxWg");
	_receiptList.Add("YOMGwAkbASNEgMibM63w4PTVKa43cHmv6rfdvHGaZjdU19f5iIE9y1EiXUyALO0R");
	_receiptList.Add("aepIhSInxFk68yvdk66cwfskjti6sBKTqPBHo6vdI5J664EpOVBYN4lwqk89n1YJ");
}
```
	  
<br>      
  
# 외부 라이브러리
  
## [HappyHTTP](./Manuals/HappyHTTP.md)
- [GitHub](https://github.com/mingodad/HappyHTTP)
- 사용하기 간편하다. (*인터페이스가 직관적*)
- 요청이 **비동기로 진행**된다.
- 파이프라이닝을 지원한다. 따라서 **응답을 대기하지 않고 여러 번 요청**할 수 있다.
- `Windows`, `Linux`, `OSX`를 지원한다.
- 응답 데이터를 콜백 함수(`OnBegin`, `OnData`, `OnComplete`)를 통해 핸들링한다.
- 별도의 라이브러리 설치 없이 **해당 라이브러리의 소스 코드만으로 사용 가능**하다.

## [WNetWrap](./Manuals/WNetWrap.md)
- [GitHub](https://github.com/hack-tramp/WNetWrap)
- 사용하기 간편하다. (*라이브러리 기능이 직관적이다.*)
- `Win32API`의 `wininet.h`의 기능을 사용하여 개발된 **Widnwos 네이티브 라이브러리**다.
- 별도의 라이브러리 설치 없이 해당 라이브러리의 **소스 코드만으로 사용 가능**하다.
- 라이브러리 내부적으로 **메모리 누수**가 존재한다.
- 멀티스레드에 안전하지 않다.
- 요청 시 `Timeout` 기능을 사용하는 경우 라이브러리 내부에서 **별도의 스레드를 생성**한다.

## [libcurl](./Manuals/libcurl.md)
- [GitHub](https://github.com/curl/curl)
- `windows` 지원
- 가장 오래되고 안정된 Client 네트워크 라이브러리.
- 응답 데이터를 콜백 함수로 핸들링한다. (*응답 데이터를 메모리 또는 파일로 저장할 수 있다.*)
- 콜백 함수를 지정하지 않으면 표준 출력 장치에(`stdout`) 자동 출력된다.

## [curlcpp](./Manuals/curlcpp.md)
- [GitHub](https://github.com/JosephP91/curlcpp)
- [Document](https://josephp91.github.io/curlcpp)
- `libcurl` 필요
- `libcurl`의 **C++ 버전**

## [curly.hpp](./Manuals/curly.hpp.md)
- [GitHub](https://github.com/BlackMATov/curly.hpp)
- [Document](http://matov.me/curly.hpp)
- `libcurl` 필요
- `libcurl`을 `C++ 17`로 랩핑한 라이브러리
- **`C++ 17` 이상** 필요
- 요청이 **비동기로 진행**된다.

## [curlite](./Manuals/curlite.md)
- [GitHub](https://github.com/grynko/curlite )  
- 사용하기 쉽다
- `libcurl` 필요
- **`C++ 11` 이상** 필요.
- **멀티스레드에서 사용 불가능.**
- **현재 개발중**

## [Swish](./Manuals/Swish.md)
- [GitHub](https://github.com/lamarrr/swish)    
- `libcurl` 필요
- **`C++ 17` 이상** 필요
- **JSON 송신 불가능.**
- 정보가 너무 부족하다. (*현재로서는 라이브러리를 직접 분석하거나, 기능을 추가해야함.*)
  
## [cpp-httplib](./Manuals/cpp-httplib.md)
- [GitHub](https://github.com/yhirose/cpp-httplib)
- 사용하기 쉽다.
- **Header-Only** 라이브러리.
- 크로스 플랫폼 지원
- 해당 라이브러리로 서버도 구현 가능.
- **`C++ 11` 이상** 필요.
- **내부적으로 `Blocking Socket`**을 사용한다. (*`non-blocking` 소켓 기능은 지원하지 않는다.*)

```c
#include <httplib.h>
#include <iostream>

int main() {

  httplib::Headers headers = {{"Content-Type", "application/json"}};
  std::string body = R"({"AuthID":"test01","AuthToken":"DUWPQCFN5DQF4P"})";
  httplib::Client cli("127.0.0.1", 11502);

  if (auto res = cli.Post("/AuthCheck", headers, body, "application/json")) {
    std::cout << res->status << std::endl;
    std::cout << res->get_header_value("Content-Type") << std::endl;
    std::cout << res->body << std::endl;
  } else {
    std::cout << "error code: " << res.error() << std::endl;
  }

  return 0;
}
```
  
## malloy (`boost` 설치 필요) 
- [GitHub](https://github.com/tectu/malloy )
- Malloy is a small, embeddable HTTP & WebSocket server & client built on top of boost.
- Windows (with both MSVC and MinGW), Linux (Ubuntu, Debian, Fedora, ...), MacOS, FreeBSD
   
## EasyHttp (`POCO` 설치 필요) 
- [GitHub](https://github.com/sony/easyhttpcpp )
- A cross-platform HTTP client library with a focus on usability and speed.