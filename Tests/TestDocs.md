# 서버 머신 사양

# 테스트 설명

## 테스트 항목
1. 테스트 시간 동안 총 몇 번의 Req/Res를 진행했는가.
2. 라이브러리 자체의 메모리 누수가 있는가?

## 테스트 방법
1. 설정한 스레드 개수 만큼 스레드 생성
2. 설정한 테스트 시간 만큼 각 스레드는 일정 시간 마다 설정한 크기의 HTTP 패킷을 송신한다.
3. 각 스레드는 서버로부터 응답을 받았을 경우 성공 횟수를 증가시킨다.
3. 테스트 시간이 종료됐으면 프로그램 종료 전에 [CRT 라이브러리](https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/find-memory-leaks-using-the-crt-library?view=msvc-170)를 사용해서 메모리 누수 체크

# 테스트 결과

## HappyHTTP

### 테스트 설정값
|||
| :-----           | :---- |
| Test Time (Sec)  | 60 |
| Worker Count     | 1 |
| Solution Config  | Debug |

### 결과
| Packet Size (bytes) | Total Count |
| :-----              | :----: |
| 1 bytes             | 3974 |
| 1,000 bytes         | 3968 |
| 1,000,000 bytes     | 3983 |

- **Thread Safed** 하다.
- **Memory Leak**이 없다.

<br>

## libcurl

### 테스트 설정값
|||
| :-----           | ----: |
| Test Time (Sec)  | 60 |
| Worker Count     | 1 |
| Solution Config  | Debug |

### 결과
| Packet Size (bytes) | Total Count |
| :-----              | :----: |
| 1 bytes             | 2775 |
| 1,000 bytes         | 2744 |
| 1,000,000 bytes     | 3634 |

- **Thread Safed** 하다.
- **Memory Leak**이 없다.

<br>

## WNetWrap

### 테스트 설정값
|||
| :-----           | ----: |
| Test Time (Sec)  | 60 |
| Worker Count     | 1 |
| Solution Config  | Debug |

### 결과
| Packet Size (bytes) | Total Count |
| :-----              | :----: |
| 1 bytes             | 3967 |
| 1,000 bytes         | 3967 |
| 1,000,000 bytes     | 3989 |

- 라이브러리 내부에서 전역 변수를 사용하고 있어서 **Thread Safed 하지 않다.** (*Lock을 걸지 않으면 에러 발생*)
- 라이브러리 자체적으로 **Memory Leak** 존재.
    - 내부에서 `std::map`을 사용하고 있는데, 노드를 삭제하지 않고 있다.
    - 공식 문서를 살펴봐도 따로 `Release`하라는 설명이나, 관련 함수가 존재하지 않는다.