# `curlite.hpp` 사용법

- 예제 코드 경로 : `/ExampleCodes/curliteExample`

## 들어가기전에

- 해당 문서에서는 `Windows` 환경에서의 설치 방법만 설명한다.

- 해당 문서에서 설명할 `curcurlite` 라이브러리는 [libcurl](https://github.com/curl/curl)을 `C++`로 랩핑한 라이브러리다. 따라서 `curlite` 라이브러리를 적용하고자 하는 프로젝트에는 최소 **7.32 버전 이상의 `libcurl` 라이브러리가 설치되어 있어야**한다. ([`libcurl` 설치 방법](~/Manuals/libcurl.md))

- 해당 라이브러리는 현재 개발중이며, 마지막 Commit 날짜는 작성일 기준 2019년 04월 12일이다.

- 해당 라이브러리는 멀티 스레드를 지원하지 않는다.

- 해당 라이브러리는 C++ 11 이상의 언어 지원이 필요하다.

## 라이브러리 설명
- C++ 11 기능 지원
- CURL 옵션 
- CURL 사용 편의성 증가
- 외부 종속성이 없는 라이브러리 (*`libcurl`은 제외*)

## 라이브러리 설치하기

1. [GitHub](https://github.com/grynko/curlite)에서 프로젝트를 다운로드한다.

2. 다운로드 한 프로젝트 폴더 내부의 다음 파일들을 자신의 프로젝트로 옮긴다.

![install_02_01](../Images/curlite/install_02.png)

3. 해당 파일들을 자신의 프로젝트에 포함시킨다.

![install_03](../Images/curlite/install_03.png)

## 예제 코드

### 예제 1. stdout에 웹 페이스 소스 쓰기
```cpp
try
{
    curlite::Easy easy;
    easy.set( CURLOPT_URL, "http://example.com" );
    easy.set( CURLOPT_FOLLOWLOCATION, true );

    std::cout << easy;
}
catch( std::exception &e ) {
    std::cerr << "Got an exception: " << e.what() << std::endl;
}
```
또는 아래와 같이 `curlite::download()` 함수를 사용해도 된다.
```cpp
try
{    
    curlite::download( "http://example.com", std::cout, true );
}
catch( std::exception &e ) 
{
    std::cerr << "Got an exception: " << e.what() << std::endl;
}
```

### 예제2. 원격 FTP 서버에 파일 업로드 및 전송 시간 표기
```cpp
try
{
    curlite::Easy easy;
    easy.set( CURLOPT_URL, "ftp://example.com/file.txt" );
    easy.set( CURLOPT_USERNAME, "username" );
    easy.set( CURLOPT_PASSWORD, "password" );
    easy.set( CURLOPT_UPLOAD, true );

    // open input file stream
    std::ifstream ifs( "file.txt", std::ios::binary );

    // start upload
    ifs >> easy;
    
    double totalSecs = easy.getInfo<double>( CURLINFO_TOTAL_TIME );
    std::cout << "Upload time: " << totalSecs << " s" << std::endl;
}
catch( std::exception &e )
{
    std::cerr << "Got an exception: " << e.what() << std::endl;
    return 1;
}
```
또는 아래와 같이 `curlite::upload()` 함수를 사용해도 된다.
```cpp
try
{
    std::ifstream ifs( "file.txt", std::ios::binary );  
    auto easy = curlite::upload( ifs, "ftp://example.com/file.txt", "username", "password" );
    
    double totalSecs = easy.getInfo<double>( CURLINFO_TOTAL_TIME );
    std::cout << "Upload time: " << totalSecs << " s" << std::endl;
}
catch( std::exception &e )
{
    std::cerr << "Got an exception: " << e.what() << std::endl;
}
```

### 예제3. JSON 송/수신하기

```cpp
#include "curl/curl.h"
#include "curlite.hpp"

const bool SendRequest(
	const char* url, 
	const char* body_data,
	const bool isSSL = false)
{
	curl_slist* header = nullptr;
	header = curl_slist_append(header, "Content-Type: application/json");
	const int32_t body_data_len = (int32_t)strlen(body_data);

	try
	{
		curlite::Easy easy;
		easy.set(CURLOPT_URL, url);
		easy.set(CURLOPT_POST, 1L);
		easy.set(CURLOPT_SSL_VERIFYPEER, isSSL);
		easy.set(CURLOPT_SSL_VERIFYHOST, isSSL);
		easy.set(CURLOPT_HTTPHEADER, header);
		easy.set(CURLOPT_POSTFIELDS, body_data);
		easy.set(CURLOPT_POSTFIELDSIZE, body_data_len);
		easy.set(CURLOPT_FOLLOWLOCATION, true);

		std::cout << easy << std::endl;
	}
	catch (std::exception& e) 
	{
		std::cerr << "Got an exception: " << e.what() << std::endl;
	}

	return true;
}

int main()
{
	const char* auth_check_url = "http://127.0.0.1:11502/AuthCheck";
	const char* inapp_check_url = "http://127.0.0.1:11502/InAppCheck";

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

	SendRequest(auth_check_url, auth_check_body_data);
	SendRequest(inapp_check_url, inapp_check_body_data);

	return 0;
}
```