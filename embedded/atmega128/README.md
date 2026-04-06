# ATmega128

ATmega128 기반 임베디드 실습 폴더입니다. GPIO 제어부터 인터럽트, PWM, UART, 센서, 외부 메모리까지 다양한 하드웨어 주제를 다룹니다.

## 폴더 구성

| 폴더 | 내용 |
| --- | --- |
| `src/` | 실습 소스 파일 |
| `lib/` | LCD, UART, 센서, EEPROM 등 공용 라이브러리 |
| `deps/` | 외부 의존성 |

## 대표 주제

- LED, 스위치, FND 제어
- 타이머와 인터럽트
- PWM, 서보, 부저, DC 모터
- UART 통신
- I2C 기반 온습도 센서
- 외부 EEPROM, LCD, PIR 센서

## 참고

- `deps/arduino-core`는 서브모듈로 연결된 외부 의존성입니다.
- 루트 `CMakeLists.txt`에서 외부 프로젝트 형태로 함께 빌드할 수 있습니다.
