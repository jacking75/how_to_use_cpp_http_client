# `curly.hpp` 사용법

- 예제 코드 경로 : `ExampleCodes/curlyExample`

## 들어가기전에

- 해당 문서에서는 `Windows` 환경에서의 설치 방법만 설명한다.

- 해당 문서에서 설명할 `curly.hpp` 라이브러리는 [libcurl](https://github.com/curl/curl)을 `C++`로 랩핑한 라이브러리다. 따라서 `curly.hpp` 라이브러리를 적용하고자 하는 프로젝트에는 `libcurl` 라이브러리가 설치되어 있어야한다. ([`libcurl` 설치 방법](~/Manuals/libcurl.md))

## 라이브러리 설치하기

1. [GitHub](https://github.com/BlackMATov/curly.hpp)에서 프로젝트를 다운로드한다.

2. 다운로드 한 프로젝트 폴더 내부의 다음 파일들을 자신의 프로젝트로 옮긴다.

![install_02_01](../Images/curly/install_02_01.png)

![install_02_02](../Images/curly/install_02_02.png)

3. 해당 파일들을 자신의 프로젝트에 포함시킨다.

![install_03](../Images/curly/install_03.png)

4. `C++` 버전 변경

![install_04](../Images/curly/install_04.png)

5. `curly.hpp` 파일 진입부에 `#define` 추가

`curly.cpp` 파일 내부에서 `std::max()`, `std::min()`을 사용하고 있는데 해당 함수의 이름이 `minwindef.h` 파일의 매크로와 동일해서 인식 에러가 발생한다.

![error_01](../Images/curly/error_01.png)

따라서 `curly.hpp` 파일에 다음과 같이 `#define NOMINMAX` 추가한다.

![install_05](../Images/curly/install_05.png)


## 라이브러리 설명



## 라이브러리 사용하기
