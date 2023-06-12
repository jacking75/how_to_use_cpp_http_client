# `curlite.hpp` 사용법

- 예제 코드 경로 : `/ExampleCodes/curliteExample`

## 들어가기전에

- 해당 문서에서는 `Windows` 환경에서의 설치 방법만 설명한다.

- 해당 문서에서 설명할 `curcurlite` 라이브러리는 [libcurl](https://github.com/curl/curl)을 `C++`로 랩핑한 라이브러리다. 따라서 `curlite` 라이브러리를 적용하고자 하는 프로젝트에는 `libcurl` 라이브러리가 설치되어 있어야한다. ([`libcurl` 설치 방법](~/Manuals/libcurl.md))

## 라이브러리 설치하기

1. [GitHub](https://github.com/grynko/curlite)에서 프로젝트를 다운로드한다.

2. 다운로드 한 프로젝트 폴더 내부의 다음 파일들을 자신의 프로젝트로 옮긴다.

![install_02_01](../Images/curlite/install_02.png)

3. 해당 파일들을 자신의 프로젝트에 포함시킨다.

![install_03](../Images/curlite/install_03.png)

## 라이브러리 사용하기

### JSON Request
```cpp
const bool DoJsonRequest(
	const char* url, 
	const char* body_data, 
	const bool isPostMethod = false,
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
		easy.set(CURLOPT_SSL_VERIFYPEER, 1L);
		easy.set(CURLOPT_SSL_VERIFYHOST, 1L);
		easy.set(CURLOPT_HTTPHEADER, header);
		easy.set(CURLOPT_POSTFIELDS, body_data);
		easy.set(CURLOPT_POSTFIELDSIZE, body_data_len);
		easy.set(CURLOPT_FOLLOWLOCATION, true);

		std::cout << easy << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Got an exception: " << e.what() << std::endl;
	}

	return true;
}
```

#### 실제 사용 예시
```cpp
#include "curl/curl.h"
#include "curlite.hpp"

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

	DoJsonRequest(auth_check_url, auth_check_body_data);
	DoJsonRequest(auth_check_url, auth_check_body_data, true);
	DoJsonRequest(inapp_check_url, inapp_check_body_data, true);

	return 0;
}
```
