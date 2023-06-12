# `Swish` 사용법

- 예제 코드 경로 : `ExampleCodes/SwishExample`

## 들어가기전에

- 해당 문서에서는 `Windows` 환경에서의 설치 방법만 설명한다.

- 해당 문서에서 설명할 `Swish` 라이브러리는 [libcurl](https://github.com/curl/curl)을 `C++`로 랩핑한 라이브러리다. 따라서 `Swish` 라이브러리를 적용하고자 하는 프로젝트에는 `libcurl` 라이브러리가 설치되어 있어야한다. ([`libcurl` 설치 방법](~/Manuals/libcurl.md))

## 라이브러리 설치하기

### 참고사항
- 예제 코드에서는 프로젝트 내부에 `thirdparty`라는 별도의 폴더를 생성하여 다음과 같이 라이브러리 파일들을 관리하고 있다.

![import_ex_thirdparty_01](../Images/Swish/import_ex_thirdparty_01.png)

1. [GitHub](https://github.com/lamarrr/swish)에서 프로젝트를 다운로드한다.

2. 다운로드 한 프로젝트 폴더 내부에서 `swish` 폴더를 자신의 프로젝트로 옮긴다.

![install_02](../Images/Swish/install_02.png)

![import_ex_thirdparty_02](../Images/Swish/import_ex_thirdparty_02.png)

3. 소스코드 Include

![install_03](../Images/Swish/install_03.png)

4. `C++` 버전 변경

![install_04](../Images/Swish/install_04.png)

5. **SDL 검사** OFF

라이브러리 내부에서 더 이상 사용중이지 않는 함수를 호출하고 있다.

![error_01](../Images/Swish/error_01.png)

따라서 빌드를 하기 위해서는 **SDL 검사**를 OFF 해야한다.

![install_05](../Images/Swish/install_05.png)


## 라이브러리 사용하기
