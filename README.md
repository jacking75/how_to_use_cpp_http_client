# `C++`로 `HTTP` 통신하기
- `C++`는 표준 라이브러리에서 `HTTP` 통신 기능을 지원하지 않기 때문에 외부 라이브러리를 사용해야한다.
- 해당 문서에서는 다양한 `C++ HTTP 라이브러리` 소개와 사용법에 대해 설명한다.

# 테스트 서버

- 서버 코드 : `FakeHiveServer`

## 설명

- `ASP.NET Core(.NET 7)` 사용.
- Packet Body 포맷으로 `JSON` 사용.

## API 설명
| Name    		| Method   	|  Decription  		| 
| -- 			| -- 		| -- 				|
| AuthCheck  	| GET   	|  인증 토큰 확인  	 | 
| AuthCheck   	| POST  	|  인증 토큰 확인  	 | 
| InAppCheck   	| POST   	|  영수증 확인  	 | 

## API Format
### AuthCheck (GET)
```shell
GET http://localhost:11502/AuthCheck
Content-Type: application/json

{
  "AuthID":"test03",
  "AuthToken":"5GZF7OFY05P4TT"
}
```  

### AuthCheck (POST)
```shell
POST http://localhost:11502/AuthCheck
Content-Type: application/json

{
  "AuthID":"test03",
  "AuthToken":"5GZF7OFY05P4TT"
}
```  

### InAppCheck
```shell
POST http://localhost:11500/InAppCheck
Content-Type: application/json

{
  "Receipt":"XbRd1nN5ct0IKWNHiULeuxhnLOfhuqHs5vOvRCKVPh0cSQrZk9Dy8q6atVkY3Bg6",
}
```  

#### `AuthCheck` 패킷 작성 시 참고 사항

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

#### `InAppCheckController` 패킷 작성 시 참고 사항

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

# `C++ HTTP` 라이브러리 목록
  
## [HappyHTTP](./Manuals/01_HappyHTTP.md)
- 직관적인 API
- 크로스 플랫폼 (`Windows`, `Linux`, `OSX`) 지원
- 다른 라이브러리 **종속성 없음**
- 모든 요청은 **비동기로 동작** (*응답 대기 불필요, 여러 번 요청 가능*)
- 응답 데이터는 **Folling** 방식으로 수신.
- 응답 데이터는 콜백 함수로 핸들링

## [WNetWrap](./Manuals/02_WNetWrap.md)
- [WinINet](https://learn.microsoft.com/en-us/windows/win32/wininet/about-wininet) API로 개발
- `Windows`만 지원
- 다른 라이브러리 **종속성 없음**
- 현재 구현된 기능

### 주의 사항
- **Memory Leak 존재**
- **멀티스레드로 사용 불가능**
- Timeout 기능 사용 시 Thread 생성됨.

## [libcurl](./Manuals/03_libcurl.md)
- **가장 오래되고 안정**된 데이터 전송 프로그램 (*CLI Tool*)
- 다양한 네트워크 기능 지원
- 응답 데이터는 콜백 함수로 핸들링 (*콜백 함수 미지정 시 `stdout`에 자동 출력*)
- 응답 데이터를 메모리 또는 파일로 저장할 수 있음.

## [curlcpp](./Manuals/04_curlcpp.md)
- `libcurl` 필요
- `libcurl`의 **C++ 버전**

## [curlite](./Manuals/05_curlite.md)
- `libcurl` 필요
- 직관적인 API
- **`C++ 11` 이상** 필요.
- **멀티스레드로 사용 불가능.**
- **현재 개발중인 라이브러리**

## [curly.hpp](./Manuals/06_curly.hpp.md)
- [Document](http://matov.me/curly.hpp)
- `libcurl` 필요
- `libcurl`을 `C++ 17`로 랩핑한 라이브러리
- **`C++ 17` 이상** 필요
- 요청이 **비동기로 진행**된다.

## [Swish](./Manuals/Swish.md)
- [GitHub](https://github.com/lamarrr/swish)    
- `libcurl` 필요
- **`C++ 17` 이상** 필요
- **JSON 송신 불가능.**
- 정보가 너무 부족하다. (*현재로서는 라이브러리를 직접 분석하거나, 기능을 추가해야함.*)
  
## [cpp-httplib](./Manuals/cpp-httplib.md)
- 직관적인 API
- 크로스 플랫폼 지원
- `C++ 11` 이상 필요
- 모든 요청은 **동기로 동작**. (*비동기 지원 X*)
- **Header-Only** 라이브러리
- 서버 기능도 지원 (*해당 문서에서는 다루지 않는다.*)
  
## malloy (`boost` 설치 필요) (TODO)
- [GitHub](https://github.com/tectu/malloy )
- Malloy is a small, embeddable HTTP & WebSocket server & client built on top of boost.
- Windows (with both MSVC and MinGW), Linux (Ubuntu, Debian, Fedora, ...), MacOS, FreeBSD
   
## EasyHttp (`POCO` 설치 필요) (TODO)
- [GitHub](https://github.com/sony/easyhttpcpp )
- A cross-platform HTTP client library with a focus on usability and speed.