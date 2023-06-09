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

## [WNetWrap](./Manuals/WNetWrap.md)

## [libcurl](./Manuals/libcurl.md)

## [curlcpp](./Manuals/curlcpp.md)
- [공식사이트](https://josephp91.github.io/curlcpp)
- `libcurl` 필요
- `libcurl`의 **C++ 버전**

## [curly.hpp](./Manuals/curly.hpp.md)
- `libcurl` 필요
- [GitHub](https://github.com/BlackMATov/curly.hpp)
- [공식 사이트](http://matov.me/curly.hpp)
- `libcurl`을 `C++ 17`로 랩핑한 라이브러리
- **비동기 요청 기능 지원**

## [curlite](./Manuals/curlite.md)
- `libcurl` 필요
- [GitHub](https://github.com/grynko/curlite )  
- 사용하기 쉽다
- **C++ 11 이상**
- **멀티스레드에서 사용 불가능.**
- **현재 개발중**

## [Swish](./Manuals/curlite.md)
- `libcurl` 필요
- [GitHub](https://github.com/lamarrr/swish)    
- **`C++ 17` 이상**
- JSON 송신 불가능.
- 정보가 너무 부족하다.
- 현재로서는 라이브러리를 직접 분석하거나, 기능을 추가해야함.
  
## Httplib (cpp-httplib) 
- A C++11 single-file header-only cross platform HTTP/HTTPS library
- Header-Only 라이브러리.
- 크로스 플랫폼 라이브러리.
- **`C++ 11` 이상** 
- 블록킹 소켓 I/O
- [GitHub](https://github.com/yhirose/cpp-httplib)
- [Sample](https://cdecl.github.io/dev/cpp-httplib-sample/ )
- [cpp-httplib + nlohmann.json를 사용하여 http 요청하기](https://docs.google.com/document/d/e/2PACX-1vTpb2n7xjHJAR0g8JEEI0BzDgzZAJkfEVTUJs5NL-yogwRGqs_nRNml99DQohaUdOxjhy1ffjaWzLtR/pub )  
- [nlohmann.json](https://github.com/nlohmann/json )
  
## malloy (`boost` 설치 필요) 
- [GitHub](https://github.com/tectu/malloy )
- Malloy is a small, embeddable HTTP & WebSocket server & client built on top of boost.
- Windows (with both MSVC and MinGW), Linux (Ubuntu, Debian, Fedora, ...), MacOS, FreeBSD
   
## EasyHttp (`POCO` 설치 필요) 
- [GitHub](https://github.com/sony/easyhttpcpp )
- A cross-platform HTTP client library with a focus on usability and speed.