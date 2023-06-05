# `WNetWrap` 사용법

예제 코드 : `../ExampleCodes/WNetWrapExample`

## 라이브러리 설치하기

1. `../ExampleCodes/WNetWrapExample`에서 `wnetwrap.cpp`와 `wnetwrap.h`를 자신의 프로젝트 폴더 복사한다.

![install](../Images/WNetWrap/install_01.png)


2. 해당 소스코드를 프로젝트에 포함시킨다. (그림 상의 솔루션 이름이 `WNetWrapExample`이지만, 실제로는 *`WNetWrap`를 사용하는 다른 프로젝트라고 가정한다.*)

![install](../Images/WNetWrap/install_02.png)


3. `C++` 버전 변경 (최소 C++17 이상의 버전이 필요하다.)

![install](../Images/WNetWrap/install_03.png)

4. `SDL 검사` OFF

![install](../Images/WNetWrap/install_04.png)

5. 라이브러리를 `#include`한다.

![install](../Images/WNetWrap/install_05.png)



<br>



## 라이브러리 설명

- Win32API를 사용한 라이브러리
- 다른 라이브러리 설치 없이 소스 코드만 있으면 사용 가능하다.

TODO : 

### 라이브러리 사용 시 참고사항

- Timeout 기능을 사용하면 라이브러리 내부에서 별도의 스레드가 생성된다.



<br>



## 예제코드

```cpp
#include <iostream>
#include "wnetwrap.h"

void SimpleGet()
{
	wrap::Response r;
	r = wrap::HttpsRequest(wrap::Url{ "https://www.postman-echo.com/get" }, 
						wrap::Header{ {"Referer","www.bla.com"},{"Content-Type","*/*"} }, 
					wrap::Parameters{ {"fruit","mango"},{"price","£3"} }
			);
	
	std::cout << std::endl << r.text << std::endl;
}

void PostJson()
{	
	wrap::Response r = wrap::HttpsRequest(
		wrap::Url{ "http://127.0.0.1:11502/AuthCheck" },
		wrap::Header{
			{"Connection", "close"},
			{"Content-type", "application/json"},
			{"Accept", "text/plain"}
		},
		wrap::Body{ R"(
			{
				"AuthID":"cov1013@com2us.com",
				"AuthToken":"Test"
			}
		)" },
		wrap::Method{ "POST" });
	std::cout << r.text << std::endl;
}

int main()
{
	PostJson();

	SimpleGet();
	
	system("PAUSE");
	return 0;
}
```