# kuhrd 개발자 교육


## C

    - 구글 슬라이드 자기소개
    - wsl 설치
    - vscode, git 설치
    - os (리눅스 wsl 사용)

- Ubuntu install
```bash
wsl --install -d Ubuntu-22.04
wsl --set-default-version 2
wsl --set-version Ubuntu-22.04 2
wsl -l -v
```

- 터미널에서 유저 정보 입력
```bash
git config --global user.email freshmea@gmail.com
git config --global user.name freshmea
```


### 1. hello.c 작성<br>
`#` -> 전처리 지시자<br>
`main` 함수 -> 엔트리 포인트<br>
함수의 리턴값의 타입과 함수이름앞의 타입은 같아야함

### 2. literal.c 작성
| 변환문자 |  |
|---|---|
| `%d` | 10진수로 표현 |
| `0%o` | 8진수로 표현 |
| `0x%x` | 16진수로 표현 |
| `%c` | 문자 |
| `%s` | 문자열(포인터) |


### 3. limit.c 작성<br>
최대 비트수 확인 ( `<limits.h>` )<br>
` #define END_HELLO "end of file\n"` => `END_HELLO`를 `"end of file\n"` 로 치환


[실습폴더](./c_example/)


---


### makefile
```makefile
TARGET = target1 target2 ...

all: ${TARGET} # make all을 명시해야하지만 처음에 명시하면 make만 했을때도 가능

target1 : $@ #앞의 hello를 찾아.c를 붙임
target2 : $@
...
# cc -o hello hello.c 실행파일과 c파일의 이름이 같으면 생략가능
# 파일이 수정된 날짜와 시간을 체크하기때문에 수정하고 바로 make 해도 적용이 된다
clean : 
	rm ${TARGET}
```
```makefile
SRCS = ${wildcard *.c}
TARGET = ${SRCS:.c=} # 확장자를 가지지 않게 함

all: ${TARGET} 

clean : 
	rm ${TARGET}
```




### 연산자
|산술연산자||
|---|---|
|`+`|더하기|
|`-`|빼기|
|`/`|나누기|
|`%`|나머지|

|증감연산자||
|---|---|
|`++`|+1|
|`--`|-1|

`전위 후위에 따라 계산 순서가 다름`

대입연산자 : `=`

관계연산자(return, true, false) : `< > <= >= == !=`<br>
`True = 1 , False = 0`

|논리연산자||
|---|---|
|`&&`|AND|
|`\|\|`|OR|
|`!`|NOT|


- 연산자 오버로딩 : 연산자를 재정의
    - 사용자정의 Type -> 구조체

삼항연산자 :  `?`

```C
printf("1 <= %d <= 9 : %s\n" ,num, (1<=num)&&(num<=9) ? "true" : "false");
// '?' 삼항 연산자 ( [조건식] ? [참] : [거짓] )
```

[compare실습](./c_example/compare.c)<br>
```c
#include <stdbool.h> <=c에서 true false 를 명시적으로 쓸때 stdbool헤더를 쓴다
```

형 변환 연산자 : `(자료형)피연산자 <= 해당 줄 이후에 다시 원래 자료형으로 돌아옴`

sizeof 연산자 : <br>
c는 메모리를 다루는 언어이기때문에 sizeof는 자주 쓰인다.<br>
피연산자의 크기를 바이트 단위로 알려줌 (1byte = 8bit)

|비트연산자|||
|---|---|---|
|`&`|AND연산자|두비트가 모두 1인 경우만 1로 계산|
|`^`|XOR연산자|두 비트가 서로다른 경우 1로 계산|
|`\|`|OR연산자|두 비트 중 하나라도 참이면 1로 계산|
|`~`|NOT연산자|1은 0으로 0은 1로 바꿈|
|`<<`|왼쪽비트이동연산자|비트를 왼쪽으로 이동|
|`>>`|오른쪽비트이동연산자|비트를 오른쪽으로 이동|


*\*tip `ctrl+h` -> 같은 글자 한번에 치환*   


---

### 조건문

#### if - else
```c
if(조건식)
{
    실행문;
}else if(조건식){
    실행문;
}else{
    실행문;
}
```

 - 난수생성
    - srand() `<stdlib.h>`
    - time(NULL) `<time.h>`

#### switch
```c
switch(조건식)
{
    case 상수식:
        실행문;
        break;
        :
        :
    defalt:
        실행문;
        break;
}
```

### 반복문

#### for

```c
for(초기식;조건식;증감식)
{
    실행문;
}
//Flow : 초기식 -> 조건식 -(참)-> 실행문 -> 증감식 -> 조건식 -(거짓)-> 종료
```
`for문은 반복횟수가 정해져 있을 때 사용`
`초기식에서 선언한 변수 =  지역변수`

#### while

```c
while(조건문)
{
    실행문;
} // Flow : 조건문 -(참)-> 실행문 -> 조건문 -(거짓)-> 종료
```
`한번은 꼭 실행문을 실행하고자 할때 do-while 사용`

#### do-while
```c
do
{
    실행문;
}while(조건문);
//Flow : 실행문 -> 조건문 -(참)-> 실행문 -> 조건문 -(거짓)-> 종료
```
`break` -> 블록 탈출(강제로 조건 False)<br>
`continue` -> 다음 루프로 이동

### 배열

`array` = 타입의 묶음(ex. int char float ... *사용자 정의 타입*)<br>
`변수명[n]` 
 - 메모리의 범위를 넘어서면 안된다(0~n-1 까지만 접근 가능)
 - 선언과 대입을 따로 할 수 있다
    - for문을 쓰게되면 번거롭기때문에 `{ , , , }`를 통해 대입을 한다


```c
int nums1[5] = {1,2,3,4,5};
int nums2[] = {1,2,3,4,5}; //입력한 만큼의 메모리 확보
int nums3[10] = {1,2,3,4,5}; //채워지지 않은 공간은 0으로 초기화
int nums4[50]; //랜덤한 값이 채워져 있음
int nums5[50] = {0}; //모든 값을 0으로 초기화, 효율성이 떨어짐
```


### 정렬(sorting)
`빅데이터에서는 한번을 순회하더라도 많은 시간이 걸리기에 어떤 알고리즘을 사용하는지가 중요`
- 데이터의 순서 변경(swap)
- swap 함수 작성
- info 함수 작성

#### 버블정렬
 : 인접한 두 원소를 비교하여 스왑하는 정렬방식<br>
`if(arr[j] > arr[j+1])`

#### 선택정렬
 : 전체에서 가장 작은 값을 찾아 앞쪽 위치와 교환하며 정렬하는 방식<br>


#### 퀵정렬
`stdlib.h`
```c
qsort(정렬할 배열의 시작주소, 배열원소개수, 원소의 크기, 비교함수이름(compare))

int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}
```
 - `void *` -> 자료형이 정해지지않은 포인터 (qsort는 범용)
 - `const` -> 값을 바꾸지 않음, 비교만
 - `(int *)a` -> a를 int형 포인터로 형변환
 - `*(int *)a` -> a가 가리키는 주소의 값


### 포인터(Pointer)
`주소값을 저장하는 변수` <br>
선언 : ` int *pValue `<br>
`pValue` -> 주소<br>
`*pValue` -> pValue주소안의 값<br>
`*` -> 참조 연산자
`&` -> 역참조 연산자
 *선언이 된 변수의 주소만 저장 및 역참조 가능*

```c    
int *p;     //1.포인터 변수 선언
int Value;
p = &Value; //2.주소 저장
*p = 200;   //3.참조 사용
```

### 포인터 사용한 구조(C)
1. 함수 함수포인터 함수명 = 포인터
```c
int (*fp)(int,int); //함수 포인터 선언 (타입이 같아야함)
fp = add; //함수 포인터에 add 함수의 주소를 할당
//fp = &add; 가능
int re = (*fp)(4,3); 
// int re = fp(4,3); 가능
```
<br>

함수의 인자로 참조 연산자(*) 쓰는 5가지 상황
 - 호출 당하는 쪽에서 호출한 쪽의 변수를 변경할 때
 - 배열을 인자로 넘길때(필수)
 - 구조체를 인자로 넘길때(선택)
 - 사용자 정의 연산(함수)을 인자로 넘길때
 - 임의의 자료 넘길때(void *)
 
<br>
2. 배열 abc[ ] 배열명 = 포인터

```c
int nums[] = {1,2,3,4,5};
int *p;
p=nums; //배열명을 넣으면 첫번째 자리의 주소값
p=&nums[0];
// p+1 -> nums[1]
```


`sudo apt install build-essential`
`sudo apt install gdb`


### 분할 컴파일

`function.h`->`함수선언`
`function.c`->`함수정의`
`main.c`->`#include "function.h"`


*[cmake사용법](./cmake사용법.md)*

[야구게임실습](./c_example/part4/baseballGame)

- static 정적변수


```c
#ifdef ~~~
#define ~~~
#endif 

#pragma once
```

### 구조체

구조체 ---> Class ---> 객체 지향 언어
절차(순서)지향 언어

- struct : 사용자 정의 타입
    내장타입 만으로는 코드가 굉장히 길어지게 된다<br>
    -> 데이터를 묶어서 다룰 때 구조체 사용


`ex) student 타입`
```c
int a
float b
    :
    :
```

`typedef A B` : 별명 붙이기(가독성 ↑)

대소문자 구분 : 식별자, 함수명, 변수명 모두 소문자 ( 사용자 정의 타입만 대문자!)


멤버 연산자 
 - `.` : 멤버 접근
 - `->` : 간접멤버 접근 연산자

```c
Date d;
Date *pD;
printf("%d-%d-%d\n", d.year, d.month, d.day);
printf("%d-%d-%d\n", (*pD).year, (*pD).month, (*pD).day); 
printf("%d-%d-%d\n", pD->year, pD->month, pD->day);
```

### 공용체, 열거형
공용체(Union) : 두 가지이상의 type을 사용간으(하나의 메모리에 접근하는 방식)

열거형(enum) : 가시성때문에 사용 , switch~case문


```c
char *ga = "asfsljflsialisjflsjfalisfj"; // 문자열 리터럴 상수, 변경이 불가능함
```



|입력 get||출력 put||
|---|---|---|---|
|*char*|*string*|*char*|*string*|
|`getc` `fgetc`|`gets` `fgets`|`putc` `fputc`|`puts` `fputs`|
|포맷||||
|`scanf` `fscanf` | `scanf_s(window)` |`printf` `fprintf` `sprintf` | `snprintf` `fflusth(FILE *)`|


#### 동적할당
- malloc
- calloc
- realloc


VLA(variable length array) -> 동적할당없이 array 사용 가능



### 자료구조(Data Structure)

선형 자료 구조
- 배열 (Array)
- 리스트 (linked list)
- 스택 (stack) Last in First out(LIFO)
- 큐 (Que) First in First out(FIFO)

비선형 자료 구조
- 트리 (이진트리,...)
- 그래프 (Graph)


WAN, LAN, MQTT, 포트포워딩

MQTT 소켓(TCP  UDP)

myQueue3 - 동적할당


---

## ATmega128

MCU(Micro Controller Unit) 사용이유 : real-time 구현을 위해.( OS로부터 독립적인 작동을 하고 정보를 주고 받는 통신을 함.)

1. `avr-gcc` → (~.c, main.c, ~.h) → `.elf` → `.hex` → upload
2. core-code → ~.h, io.h
3. avrdude install

```cmake
//최상위 CMAKE

include(ExternalProject)

ExternalProject_Add(atmega128_project
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/atmega128
	BINARY_DIR ${CMAKE_BINARY_DIR}/atmega128-build
	CMAKE_ARGS
		-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/atmega128/avr-toolchain.cmake
		-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	INSTALL_COMMAND ""
)
```

```cmake
//atmega128 디렉토리의 CMAKE

cmake_minimum_required(VERSION 3.10)

# standalone configure일 때만 기본 AVR 툴체인 파일을 지정한다.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/avr-toolchain.cmake")
endif()

project(Atmega128_Project C)

# --- 하드웨어 설정 ---
set(MCU atmega128)
set(F_CPU 16000000UL)
set(PROG_TYPE stk500v2)
set(PROG_PORT usb)

# --- 실행 파일 및 옵션 ---
add_executable(${PROJECT_NAME}.elf src/main.c)

target_compile_options(${PROJECT_NAME}.elf PUBLIC
    -mmcu=${MCU}
    -DF_CPU=${F_CPU}
    -Os -Wall
)

target_link_options(${PROJECT_NAME}.elf PUBLIC -mmcu=${MCU})

# --- 빌드 후처리 (HEX 생성) ---
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND avr-objcopy -j .text -j .data -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND avr-size --format=avr --mcu=${MCU} ${PROJECT_NAME}.elf
    COMMENT "Generating Intel HEX file and analysis"
)

# --- 업로드 타겟 추가 ---
add_custom_target(upload
    COMMAND avrdude -p m128 -c ${PROG_TYPE} -P ${PROG_PORT} -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Flashing ${PROJECT_NAME}.hex to hardware..."
)



//arv-toolchain.cmake 파일

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# 컴파일러 지정
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

# 호스트(PC) 라이브러리 참조 방지
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```
```shell
 git submodule add https://github.com/arduino/ArduinoCore-avr.git deps/arduino-core
 #github에서 submodule 해서 deps파일에
 sudo apt install gcc-avr avr-libc binutils-avr
 sudo apt install usbutils
 winget install --interactive --exact dorssel.usbipd-win
 ```

 lsusb → wsl 환경이어서 나오지 않음

 ```powershell
 #윈도우 powershell 에서 usbipd 설치

winget install --interactive --exact dorssel.usbipd-win
usbipd list
usbipd bind --busid 4-4
usbipd attach --wsl --busid <busid>
```

```shell
lsusb #확인
#Bus 001 Device 002: ID 03eb:2104 Atmel Corp. AVR ISP mkII
#권한 변경
ls -al /dev/bus/usb/001/002
crw-rw-r-- 1 root root 189, 1 Mar 23 14:45 /dev/bus/usb/001/002
sudo chmod 666 /dev/bus/usb/001/002
ls -al /dev/bus/usb/001/002
crw-rw-rw- 1 root root 189, 1 Mar 23 14:45 /dev/bus/usb/001/002

sudo apt install avrdude
make upload
```

```shell
#usb 권한 자동 부여
sudo nano /etc/udev/rules.d/99-avrisp.rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2104", MODE="0666"

sudo udevadm control --reload-rules
sudo udevadm trigger
```


---

## atmega128/src 공부 정리

`atmega128/src` 폴더의 예제들은 LED, 스위치, FND, 타이머, 인터럽트를 단계적으로 익히기 좋게 구성되어 있다. 아래 내용은 각 `.c` 파일을 보면서 공부해야 할 핵심 포인트를 정리한 것이다.

### 1. 입출력 포트 제어의 기본

- `DDRx` 레지스터는 입출력 방향을 설정한다.
- `PORTx` 레지스터는 출력값을 내보낼 때 사용한다.
- `PINx` 레지스터는 입력 상태를 읽을 때 사용한다.
- 예제에서 `DDRC = 0x0F;` 는 C포트의 하위 4비트를 출력으로 사용하겠다는 뜻이다.
- `DDRE = 0x00;` 는 E포트를 입력으로 사용하겠다는 뜻이다.

```c
DDRC = 0x0F;
PORTC = 0x0F;
```

- LED를 켜고 끄는 가장 기본적인 흐름은 `출력 방향 설정 -> 출력값 기록` 순서로 이해하면 된다.
- `main.c`, `led2.c` 를 보면 같은 LED 제어라도 직접 주소 접근과 레지스터 이름 사용 두 가지 방식이 나온다.
- `*(volatile uint8_t *)(0x14)` 같은 표현은 메모리 맵 I/O를 직접 다루는 방법이므로, 레지스터가 실제로 메모리에 매핑되어 있다는 개념도 함께 공부하면 좋다.

### 2. LED 제어를 통해 보는 비트 연산

#### `led2.c`
- LED 전체를 한 번에 켜고 끄는 가장 기초적인 출력 예제이다.
- `_delay_ms()` 를 사용해 사람이 눈으로 볼 수 있는 속도로 변화시킨다.

#### `led3.c`
- `uint8_t led_data` 값을 0부터 증가시키면서 LED 출력 패턴을 만든다.
- 4개의 LED를 2진수처럼 생각하면 `0x00 ~ 0x0F` 범위가 왜 중요한지 이해할 수 있다.
- 이 예제를 통해 16진수와 비트 패턴의 관계를 같이 공부하면 좋다.

#### `led4.c`
- `<<` 왼쪽 시프트 연산으로 LED가 한 칸씩 이동하는 패턴을 만든다.
- `0x01 -> 0x02 -> 0x04 -> 0x08` 처럼 값이 변하는 흐름을 직접 손으로 써보면 비트 이동이 더 잘 보인다.
- `0x10` 이 되면 다시 `0x01` 로 돌아가는 부분은 순환 패턴 제어의 기본 예시이다.

### 3. 스위치 입력 처리

#### `switch1.c`
- `PINE >> 4` 로 상위 4비트를 하위 4비트 위치로 옮겨 읽고 있다.
- 왜 시프트를 하는지, 실제 스위치가 어느 비트에 연결되어 있는지 회로와 함께 보면 이해가 쉬워진다.
- 입력값을 그대로 LED 출력에 연결하는 구조라서 "입력을 읽어 출력으로 바로 반영"하는 가장 단순한 예제이다.

#### `switch2.c`
- 스위치 상태에 따라 LED 깜빡임 속도를 다르게 만드는 예제이다.
- `switch_flag_pre` 에 마지막 유효 입력을 저장하는 방식은 상태 기억의 기초이다.
- `PORTC ^= 0x0F;` 는 XOR 연산으로 LED 상태를 반전시키는 코드이므로 비트 토글 개념을 공부하기 좋다.
- 입력값에 따라 지연 시간을 다르게 두는 부분을 통해 조건문과 하드웨어 반응 속도의 관계를 같이 볼 수 있다.

### 4. FND(7-Segment) 표시 원리

#### `fnd1.c`
- 숫자나 문자를 표시하기 위해 세그먼트 패턴 테이블을 배열로 저장해 둔 예제이다.
- 배열의 인덱스와 실제 출력 모양이 연결된다는 점이 중요하다.
- `FND_DATA_TBL[i]` 처럼 테이블 기반으로 제어하면 하드웨어 출력 코드가 단순해진다.

#### 공부 포인트
- 왜 숫자 0이 `0x3F` 인지, 각 비트가 어떤 세그먼트를 의미하는지 직접 표로 정리해 보기
- 공통 애노드/공통 캐소드에 따라 값이 달라질 수 있다는 점 확인하기
- 배열을 사용한 하드웨어 제어가 왜 편한지 이해하기

### 5. 타이머를 이용한 시간 제어

#### `fnd2.c`, `test.c`
- `_delay_ms()` 없이 타이머 오버플로우 인터럽트로 시간을 세는 방식이다.
- `volatile uint8_t milliseconds` 는 인터럽트에서 값이 바뀌므로 `volatile` 로 선언되어 있다.
- `TCCR0`, `TIMSK`, `TOIE0` 설정을 통해 Timer0 오버플로우 인터럽트를 활성화한다.
- 일정 횟수 이상 오버플로우가 발생하면 숫자를 바꾸는 구조이므로, "소프트웨어 지연"이 아니라 "하드웨어 타이머 기반 주기 제어"라는 점이 중요하다.

```c
TCCR0 = _BV(CS02) | _BV(CS01) | _BV(CS00);
TIMSK = _BV(TOIE0);
sei();
```

#### 추가로 공부할 것
- 분주비가 무엇인지
- 타이머 카운터가 어떤 속도로 증가하는지
- 오버플로우가 몇 ms 간격으로 발생하는지 계산하는 방법
- `_BV(bit)` 매크로가 왜 자주 쓰이는지

### 6. 외부 인터럽트의 기본

#### `interrupt1.c`
- 폴링 방식이 아니라, 특정 핀에서 이벤트가 발생했을 때 자동으로 ISR이 실행되는 구조이다.
- `EICRB` 에서 인터럽트 발생 조건을 설정하고, `EIMSK` 에서 해당 인터럽트를 허용한다.
- `time_stop` 값을 ISR에서 바꾸고, 메인 루프는 그 값을 보고 LED 이동을 멈추거나 다시 진행한다.
- 즉, 인터럽트는 "이벤트 감지", 메인 루프는 "동작 수행"으로 역할이 나뉘어 있다.

#### 공부 포인트
- 폴링과 인터럽트의 차이
- 상승 에지, 하강 에지, 레벨 트리거의 차이
- ISR 안에서는 왜 짧고 단순하게 작성하는 것이 좋은지

### 7. 인터럽트와 FND를 결합한 예제

#### `interrupt_fnd.c`
- INT4를 누르면 숫자가 증가하고, INT5를 누르면 숫자가 감소한다.
- 메인 루프는 화면 출력만 담당하고, 값 변경은 ISR이 담당한다.
- 이 구조는 임베디드에서 자주 쓰는 "메인 루프 + 인터럽트 이벤트 처리" 구조의 좋은 예시이다.
- `% 10` 연산으로 0~9 범위를 순환시키는 방법도 같이 익혀두면 좋다.

#### `switch_fnd.c` 와 비교해서 보기
- `switch_fnd.c` 는 입력 변화를 계속 감시하는 폴링 방식이다.
- `interrupt_fnd.c` 는 하드웨어 인터럽트가 발생했을 때만 처리한다.
- 같은 기능을 두 가지 방식으로 구현한 예제이므로, CPU 점유율과 코드 구조 차이를 비교하며 공부하면 좋다.

### 8. `volatile` 키워드를 꼭 이해하기

- `volatile` 은 값이 예상치 못한 시점에 바뀔 수 있음을 컴파일러에게 알려주는 키워드이다.
- 인터럽트 서비스 루틴과 메인 함수가 함께 쓰는 변수에는 `volatile` 이 매우 중요하다.
- 이 키워드가 없으면 컴파일러 최적화 때문에 값이 바뀌었는데도 main에서 반영되지 않는 문제가 생길 수 있다.
- 이 폴더에서는 `milliseconds`, `timer0_cnt`, `cnt`, `time_stop` 같은 변수들이 대표적인 예시이다.

### 9. 이 예제들로 꼭 익혀야 할 레지스터

- `DDRA`, `DDRC`, `DDRE`
- `PORTA`, `PORTC`
- `PINE`
- `TCCR0`, `TCNT0`, `TIMSK`
- `EICRB`, `EIMSK`, `EIFR`
- `SREG`, `sei()`, `cli()`

### 10. 예제들을 보며 스스로 점검할 내용

- 왜 출력 포트와 입력 포트를 따로 설정해야 하는지 설명할 수 있는가
- 비트 시프트와 비트 마스크를 보고 어떤 하드웨어 동작이 일어나는지 말할 수 있는가
- 폴링 방식과 인터럽트 방식의 차이를 설명할 수 있는가
- `_delay_ms()` 방식과 타이머 방식의 차이를 설명할 수 있는가
- FND 테이블 값을 보고 어떤 숫자가 출력되는지 유추할 수 있는가
- ISR과 main이 동시에 같은 변수를 사용할 때 주의할 점을 설명할 수 있는가

### 11. 파일별로 다시 볼 때의 학습 순서 추천

1. `led2.c` -> `led3.c` -> `led4.c`
2. `switch1.c` -> `switch2.c`
3. `fnd1.c` -> `switch_fnd.c`
4. `fnd2.c` 또는 `test.c`
5. `interrupt1.c` -> `interrupt_fnd.c`
6. 마지막으로 `timer0led.c` 를 보면서 타이머와 LED 제어를 함께 정리하기

### 12. `timer0led.c` 에서 꼭 볼 부분

- Timer0 오버플로우가 발생할 때마다 ISR이 실행된다.
- ISR 내부에서 `TCNT0 = 112;` 로 다시 값을 넣는 것은 원하는 주기를 맞추기 위한 재설정이다.
- 메인 루프는 `timer0_cnt == 100` 이 되었을 때만 LED 데이터를 증가시킨다.
- 즉, "인터럽트는 짧은 주기 카운트", "메인 루프는 큰 동작 처리"로 역할을 분리한 예제라고 볼 수 있다.

### 13. 전체적으로 정리하면

- 이 폴더의 예제들은 단순히 LED를 켜는 코드가 아니라, AVR 마이크로컨트롤러의 입출력 구조를 익히는 과정이다.
- 먼저 포트 제어와 비트 연산을 이해하고, 그 다음 스위치 입력과 FND 출력으로 확장한 뒤, 마지막에 타이머와 인터럽트로 넘어가는 흐름으로 공부하면 좋다.
- 코드 한 줄 한 줄의 의미를 레지스터 기준으로 해석하는 연습을 하면 이후 UART, PWM, ADC 같은 주변장치 학습에도 큰 도움이 된다.

### 14. 이후 추가한 `src` 파일 공부 정리

- 최근에는 LED, 스위치, FND 중심 예제에서 더 나아가 UART와 LCD를 함께 다루는 예제들이 추가되었다.
- 이 파일들은 "외부와 데이터 주고받기"와 "문자 화면 출력"을 다루기 시작한다는 점에서 이전 단계보다 실전 느낌이 강하다.
- 특히 UART는 PC와 보드 사이의 통신, LCD는 보드 쪽의 시각적 출력 장치라는 점에서 같이 공부하면 좋다.

#### `uart1.c`

- UART0 레지스터를 직접 설정해서 시리얼 수신을 처리하는 가장 기초적인 예제이다.
- `UCSR0A`, `UCSR0B`, `UCSR0C`, `UBRR0H`, `UBRR0L` 이 각각 어떤 역할을 하는지 익히기 좋다.
- `getch()` 함수는 수신 버퍼에 데이터가 들어올 때까지 기다렸다가 `UDR0` 값을 읽는다.
- 수신한 문자가 `'0' ~ '9'` 범위이면 그 값에 맞는 FND 패턴을 `PORTA` 로 출력한다.

#### 공부 포인트
- 보레이트 설정이 왜 `UBRR0L = 0x07` 인지 계산해 보기
- `RXC0`, `UDRE0` 같은 비트 이름이 어떤 상태를 의미하는지 데이터시트와 함께 보기
- UART 수신 데이터가 단순 문자이지만, 내부적으로는 바이트 값이라는 점 이해하기

#### `uart2.c`

- `uart1.c` 와 같은 동작을 조금 더 라이브러리화한 예제이다.
- `lib/uart0` 의 `uart0Init()`, `uart0Transmit()`, `uart0Receive()` 를 사용한다.
- `FDEV_SETUP_STREAM` 으로 `stdin`, `stdout` 을 UART에 연결해서 `scanf`, `printf` 를 사용할 수 있게 만든 점이 핵심이다.
- 즉, 레지스터 직접 접근에서 표준 입출력 기반 UART 사용으로 한 단계 추상화된 구조라고 볼 수 있다.

```c
FILE OUTPUT = FDEV_SETUP_STREAM(uart0Transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT = FDEV_SETUP_STREAM(NULL, uart0Receive, _FDEV_SETUP_READ);
stdin = &INPUT;
stdout = &OUTPUT;
```

#### 공부 포인트
- 왜 임베디드에서도 `printf`, `scanf` 를 쓸 수 있는지 이해하기
- 라이브러리 함수로 분리했을 때 코드가 어떻게 더 읽기 쉬워지는지 비교하기
- `uart1.c` 와 `uart2.c` 를 비교하면서 "직접 제어"와 "함수화"의 차이 정리하기

#### `lcd1.c`

- 문자 LCD를 초기화하고, 지정한 위치에 문자열을 출력하는 가장 기초적인 LCD 예제이다.
- `lcdInit()`, `lcdClear()`, `lcdGotoXY()`, `lcdDataWrite()`, `lcdPrintData()` 함수의 역할을 파악하기 좋다.
- 한 글자씩 출력하는 방법과 문자열을 한 번에 출력하는 방법이 함께 들어 있다.
- LCD는 FND와 달리 숫자뿐 아니라 문자를 직접 보여줄 수 있어서, 사용자 인터페이스의 범위가 넓어진다.

#### 공부 포인트
- `lcdGotoXY(row, col)` 의 좌표 개념을 실제 LCD 화면과 대응해서 보기
- `lcdDataWrite()` 와 `lcdPrintData()` 의 차이 이해하기
- LCD 초기화가 왜 필요한지, 전원 인가 직후 LCD 상태와 함께 생각해 보기

#### `uart3.c`

- UART와 LCD, 외부 인터럽트를 함께 사용하는 복합 예제이다.
- UART로 들어온 문자를 LCD에 출력하고, INT4~INT7 인터럽트가 발생하면 그 정보를 직렬 모니터로 다시 보낸다.
- 이전 예제들이 한 개 주변장치씩 익히는 구조였다면, 이 파일은 여러 기능을 합쳐 보는 연습에 가깝다.
- 실제 임베디드 프로젝트는 이런 식으로 입력 장치, 통신 장치, 출력 장치를 동시에 다루는 경우가 많다.

#### 공부 포인트
- `stdin`, `stdout` 을 UART로 연결한 상태에서 `fgetc(stdin)` 와 `printf()` 가 어떻게 동작하는지 보기
- `lcdDataWrite()` 로 받은 문자를 바로 LCD에 표시하는 흐름 이해하기
- 인터럽트가 발생했을 때 ISR에서는 상태값만 바꾸고, 실제 출력은 메인 루프에서 처리하는 구조 익히기
- UART 입력, LCD 출력, 인터럽트 이벤트가 동시에 섞일 때 어떤 순서로 동작하는지 손으로 추적해 보기

#### `uart3.c` 에서 주의해서 볼 점

- `count` 같은 변수는 초기화를 하지 않으면 예상하지 못한 값에서 시작할 수 있다.
- 문자를 LCD에 찍은 뒤 숫자까지 이어서 찍으면 `a0a1a2` 같은 결과가 나올 수 있는데, 이는 코드의 동작 순서를 그대로 반영한 것이다.
- `cursor` 값을 증가시키며 줄바꿈 위치를 제어하는 부분은 "화면 버퍼 없이 LCD 좌표를 직접 관리"하는 예시로 볼 수 있다.
- ISR 안에서 `cli()` 와 `sei()` 를 다시 쓰는 것은 학습용으로 볼 수는 있지만, 보통 ISR 진입 시 인터럽트는 이미 막혀 있다는 점도 함께 알아두면 좋다.

### 15. 새로 추가된 예제들을 보는 추천 순서

1. `uart1.c`
2. `uart2.c`
3. `lcd1.c`
4. `uart3.c`

- 이 순서로 보면 "UART 직접 제어 -> UART 함수화 -> LCD 출력 -> UART + LCD + 인터럽트 결합" 흐름으로 자연스럽게 이어진다.
- 특히 `uart1.c` 와 `uart2.c` 를 먼저 비교해 보면, 이후 다른 주변장치를 라이브러리로 분리할 때 감이 빨리 잡힌다.
- 마지막에 `uart3.c` 를 보면 단일 기능 예제가 실제 응용 예제로 확장되는 흐름을 이해하기 좋다.
