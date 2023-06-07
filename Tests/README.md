# 테스트 서버 사양

- 테스트 서버 프로세스는 `~/FakeServer`를 사용한다.

# 테스트 내용

## 테스트 항목
1. 테스트 시간 동안 총 몇 번의 요청/응답을 진행했는가.
2. 라이브러리에 메모리 누수가 있는가?
3. 라이브러리가 멀티 스레드에 안전한가?

## 테스트 시나리오
0. 설정한 개수 만큼 스레드 생성 (*멀티 스레드 테스트 전용. 실제 성능 테스트시에는 스레드 1개로 진행*)
1. 설정한 시간만큼 HTTP Request 송신.
2. 서버로부터 Response를 수신 받은 경우 성공 횟수 증가.
3. 테스트 종료 후 [CRT 라이브러리](https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170)를 통해 메모리 누수 확인.

## 테스트 결과

### 1. 메모리 누수 테스트

Library     | Memory Leak |
:-------    | :---------: |
`HappyHTTP` | No          | 
`libcurl`   | No          |
`WNetWap`   | Yes         |

### 2. 멀티 스레드 안전성 테스트

Library     | Thread Safe |
:-------    | :---------: |
`HappyHTTP` | Yes         |
`libcurl`   | Yes         | 
`WNetWap`   | No          |

### 3. 성능 테스트

API         | Library    | Test Time(sec)  | Total Count  |
:-------    |:-------    | :-------------: | :----------: |
`AuthCheck` |`HappyHTTP` | 60              |              |
`AuthCheck` |`libcurl`   | 60              |              |
`AuthCheck` |`WNetWap`   | 60              |              |

API          | Library    | Test Time(sec)  | Total Count  |
:-------     |:-------    | :-------------: | :----------: |
`InAppCheck` |`HappyHTTP` | 60              |              |
`InAppCheck` |`libcurl`   | 60              |              |
`InAppCheck` |`WNetWap`   | 60              |              |