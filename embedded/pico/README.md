# Pico / Pico 2 W

Raspberry Pi Pico와 Pico 2 W 기반 실습 폴더입니다. 기본 GPIO 예제부터 MQTT 연결 예제까지 포함합니다.

## 폴더 구성

| 폴더 | 내용 |
| --- | --- |
| `src/` | 직접 작성한 실습 코드 |
| `src/mqtt/` | MQTT 관련 설정 파일 |
| `deps/pico-sdk/` | Pico SDK 서브모듈 |
| `pico-examples/` | 공식 예제 참고용 코드 |

## 대표 파일

- `src/blink.c`: 기본 GPIO 예제
- `src/buzzermario.c`: 부저 활용 예제
- `src/dht22_mqtt.c`: 센서와 MQTT를 결합한 예제
- `project_ex.md`: 프로젝트 관련 메모

## 참고

- `deps/pico-sdk`는 서브모듈로 관리됩니다.
- 루트 `CMakeLists.txt`에서 외부 프로젝트로 빌드되도록 연결되어 있습니다.
- 기본 보드는 `pico2_w`로 설정되어 있으며, 필요하면 CMake에서 `-DPICO_BOARD=pico_w`처럼 바꿔서 사용할 수 있습니다.
