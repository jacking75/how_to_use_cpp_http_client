# C++에서 http 요청하는 방법
C++ 이후에 나온 언어들은 인터넷 시대에 나와서 대부분 표준 라이브러리에서 http 통신 기능을 지원하고 있다.  
그러나 C++는 아직까지 표준 라이브러리에서 http 통신을 지원하지 않아서 http 요청을 할 때 타 언어에 비해서 불편하다.  
`Win32 API`, 외부 라이브러리를 사용하여 http 요청하는 방법을 정리한다.  
  

# 외부 라이브러리  
  
## HappyHTTP
- `HappyHTTP` 디렉토리에 코드가 있다.
- 백업 목적으로 [원 저장소](https://github.com/mingodad/HappyHTTP )에서 가져온 것이다.
- Windows, Linux 지원  
- 사용하기 쉬움. 예제 코드가 있음
  
<br>    


## Httplib (cpp-httplib) 
- A C++11 single-file header-only cross platform HTTP/HTTPS library
- This library uses 'blocking' socket I/O
  
- [Httplib (cpp-httplib) Sample](https://cdecl.github.io/dev/cpp-httplib-sample/ )
- [cpp-httplib + nlohmann.json를 사용하여 http 요청하기](https://docs.google.com/document/d/e/2PACX-1vTpb2n7xjHJAR0g8JEEI0BzDgzZAJkfEVTUJs5NL-yogwRGqs_nRNml99DQohaUdOxjhy1ffjaWzLtR/pub )  
    - [nlohmann.json](https://github.com/nlohmann/json )
  
<br>  
  

## WNetWrap
- `WNetWrap` 디렉토리에 코드가 있다.
- 백업 목적으로 [원 저장소](https://github.com/hack-tramp/WNetWrap )에서 가져온 것이다.
- Win32 API인 `WinInet`을 사용하여 별도의 외부라이브러리가 필요 없고, HTTPS도 지원. 당연히 Windows만 지원한다  
   
예제 코드: POST Requests  
```
wrap::Response r = wrap::HttpsRequest(wrap::Url{"http://www.httpbin.org/post"},
                   wrap::Payload{{"key", "value"}}, 
		   wrap::Method{"POST"});
std::cout << r.text << std::endl;

/*
 * {
 *   "args": {},
 *   "data": "",
 *   "files": {},
 *   "form": {
 *     "key": "value"
 *   },
 *   "headers": {
 *     ..
 *     "Content-Type": "application/x-www-form-urlencoded",
 *     ..
 *   },
 *   "json": null,
 *   "url": "http://www.httpbin.org/post"
 * }
 */
```  

<br>    
  

## libcurl    
우분투에서 라이브러리 설치하기  
```
sudo apt install libcurl4-openssl-dev
```

- [libcurl 공식 Tutorial 번역](https://docs.google.com/document/d/e/2PACX-1vQeGYH_LQigaj8rh8Ers2MVoopAdCuFacnnH2DHKF1Ie0qxUlcdK5_uwwlnVah5zX9DR39kEONUILie/pub )
     
  

### 간단한 Post 요청 코드
[출처](https://qiita.com/ekzemplaro/items/97bc000576a6210a3068 )     
```
#include	<string>
#include	<iostream>
#include	<cstring>

#include	<curl/curl.h>

using namespace std;

// --------------------------------------------------------------------
size_t callBackFunk(char* ptr, size_t size, size_t nmemb, string* stream)
{
	int realsize = size * nmemb;
	stream->append(ptr, realsize);
	return realsize;
}

// --------------------------------------------------------------------
string url_post_proc (const char url[],const char post_data[])
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	string chunk;

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(post_data));
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunk);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (string*)&chunk);
		curl_easy_setopt(curl, CURLOPT_PROXY, "");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	
    if (res != CURLE_OK) {
		cout << "curl error" << endl;
		exit (1);
	}

	return chunk;
}

// --------------------------------------------------------------------
int main (int argc,char *argv[])
{
	cerr << "*** 시작 ***\n";

	char url_target[] = "https://httpbin.org/post";
	char post_data[] = "user=jiro&password=123456";

	string str_out = url_post_proc (url_target,post_data);

	cout << str_out << "\n";

	cerr << "*** 종료 ***\n";

	return 0;
}
```  
  

### 간단한 Get 요청 코드
[출처](https://qiita.com/ekzemplaro/items/e19daeef842b376a37ce )     
```
#include	<string>
#include	<iostream>

#include	<curl/curl.h>

using namespace std;

// --------------------------------------------------------------------
size_t callBackFunk(char* ptr, size_t size, size_t nmemb, string* stream)
{
	int realsize = size * nmemb;
	stream->append(ptr, realsize);
	return realsize;
}

// --------------------------------------------------------------------
string url_get_proc (const char url[])
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	string chunk;

	if (curl)
		{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunk);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (string*)&chunk);
		curl_easy_setopt(curl, CURLOPT_PROXY, "");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		}
	if (res != CURLE_OK) {
		cout << "curl error" << endl;
		exit (1);
	}

	return chunk;
}

// --------------------------------------------------------------------
int main (int argc,char *argv[])
{
	cerr << "*** 시작 ***\n";

	char url_target[] = "https://httpbin.org/get";

	string str_out = url_get_proc (url_target);

	cout << str_out << "\n";

	cerr << "*** 종료 ***\n";

	return 0;  
```  
  
<br>    
  

## curlcpp
- `libcurl`의 C++ 버전이다.  
- [GitHub](https://github.com/JosephP91/curlcpp )  
- [공식사이트](https://josephp91.github.io/curlcpp  )
- `libcurl` 라이브러리 설치가 필요하다

<br>    


## curly.hpp
- [공식 사이트](http://matov.me/curly.hpp/ )
- Simple cURL C++17 wrapper  
- Asynchronous requests
- `libcurl` 라이브러리 설치가 필요하다
  
예제코드: POST  
```
auto request = net::request_builder()
    .method(net::http_method::POST)
    .url("http://www.httpbin.org/post")
    .header("Content-Type", "application/json")
    .content(R"({"hello" : "world"})")
    .send();

auto response = request.take();
std::cout << "Body content: " << response.content.as_string_view() << std::endl;
std::cout << "Content Length: " << response.headers["content-length"] << std::endl;

// Body content: {
//     "args": {},
//     "data": "{\"hello\" : \"world\"}",
//     "files": {},
//     "form": {},
//     "headers": {
//         "Accept": "*/*",
//         "Content-Length": "19",
//         "Content-Type": "application/json",
//         "Host": "www.httpbin.org",
//         "User-Agent": "cURL/7.54.0"
//     },
//     "json": {
//         "hello": "world"
//     },
//     "origin": "37.195.66.134, 37.195.66.134",
//     "url": "https://www.httpbin.org/post"
// }
// Content Length: 389
```

<br>       
  

## Curlite
- [GitHub](https://github.com/grynko/curlite )  
- 사용하기 쉽다
- C++ 11 이상 필요
- `libcurl` 라이브러리 설치가 필요하다  
  
<br>
  

## Swish
- [GitHub](https://github.com/lamarrr/swish )    
- C++ 17 이상 필요
- `libcurl` 라이브러리 설치가 필요하다 
  
<br>  
  

## malloy     
- [GitHub](https://github.com/tectu/malloy )
- Malloy is a small, embeddable HTTP & WebSocket server & client built on top of boost.
- Windows (with both MSVC and MinGW), Linux (Ubuntu, Debian, Fedora, ...), MacOS, FreeBSD
   
<br>   
  
  
## EasyHttp
- [GitHub](https://github.com/sony/easyhttpcpp )
- A cross-platform HTTP client library with a focus on usability and speed. \
- POCO C++ Libraries 필요  





