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





|통신 | 동기 | 비동기|
|---|---|---|
|멀티디바이스 | I2C, TWI | CAN, 1-Wire|
|점대점|SPI | uart|

### 16. 새롭게 추가된 AVR 예제 학습 정리

#### `pwmled.c`

- PWM 신호를 이용해 LED 밝기를 서서히 올리고 내리는 기본 예제이다.
- 기본은 `PB4(OC0)` 를 사용하지만, 주석 블록을 바꿔서 `PB5(OC1A)`, `PB6(OC1B)`, `PB7(OC2)` 도 실험할 수 있게 정리되어 있다.
- `brightness` 값이 0에서 255까지 변하면서 duty cycle 이 바뀌고, 그에 따라 LED 밝기도 달라진다.
- "단순 ON/OFF" 와 "PWM 밝기 제어" 의 차이를 체감하기 좋은 파일이다.

#### 공부 포인트
- `OCR0`, `OCR1A`, `OCR1B`, `OCR2` 가 각각 어떤 PWM 출력과 연결되는지 정리하기
- `PB4`, `PB5`, `PB6`, `PB7` 이 각각 어느 타이머의 OC 핀인지 데이터시트와 함께 보기
- `brightness += delta` 구조가 왜 부드러운 페이드 인/아웃 효과를 만드는지 이해하기

#### `pwmbuzzer.c`

- `PB7(OC1C)` 에 연결된 버저를 PWM으로 구동해서 도레미 음계를 순서대로 재생하는 예제이다.
- `ICR1` 로 주기를 만들고, `OCR1C = ICR1 / 2` 로 50% duty cycle 사각파를 만들어 버저를 울린다.
- LED PWM 과 원리는 비슷하지만, 여기서는 "밝기" 대신 "주파수" 가 바뀌어서 소리 높낮이가 달라진다.
- 즉, PWM 의 개념이 빛 제어뿐 아니라 소리 생성에도 그대로 응용된다는 점을 보기 좋다.

#### 공부 포인트
- PWM 이 LED 밝기 제어뿐 아니라 버저 음 생성에도 사용될 수 있다는 점 이해하기
- `ICR1 = 클럭 / 주파수` 형태가 왜 음 높이를 결정하는지 계산해 보기
- `CS10`, `CS00` 같은 비트 이름이 타이머별로 어떻게 다른지 비교하기

#### `buzzermario.c`

- `PB7(OC1C)` 버저를 이용해 게임풍 멜로디를 반복 재생하는 응용 예제이다.
- `play_note()` 함수로 "주파수 + 길이" 단위를 묶어서 재생하기 때문에, 단순 음계 예제보다 구조가 조금 더 함수화되어 있다.
- `_delay_ms()` 에 가변 시간을 직접 넘기지 않고, `delay_ms_variable()` 로 1ms씩 누적하는 방식도 함께 볼 수 있다.
- 즉, "버저로 한 음 내기" 에서 한 단계 더 나아가 "짧은 곡 재생" 구조를 익히는 예제라고 볼 수 있다.

#### 공부 포인트
- 음의 높이와 길이를 각각 분리해서 관리하면 코드가 왜 더 읽기 쉬워지는지 보기
- 쉼표(`NOTE_REST`) 를 넣는 것이 멜로디 리듬에 어떤 영향을 주는지 직접 들어보기
- 버저 같은 단순 출력장치도 함수화하면 재사용성이 높아진다는 점 정리하기

#### `dc_pwm_vr.c`

- DC 모터를 PWM 으로 제어하되, 가변저항(ADC 입력) 값을 이용해 속도를 조절하는 예제이다.
- `PB5(OC1A)` 로 PWM 출력, `PD4`, `PD5` 로 모터 방향 제어를 한다.
- ADC 값 `0~1023` 을 PWM duty 값으로 변환해서 모터 속도를 바꾸고, 너무 작은 duty 에서는 모터가 아예 안 도는 문제를 줄이기 위해 최소 duty 값도 둔 점이 특징이다.
- 센서 입력(ADC) 과 액추에이터 출력(PWM) 이 바로 연결되는 구조라서 제어 기초를 익히기 좋다.
- 즉, 입력값을 읽어 바로 출력 제어에 반영하는 가장 기본적인 피드백 구조를 연습하기 좋다.

#### 공부 포인트
- 왜 모터는 LED와 달리 낮은 duty 에서 반응이 거의 없을 수 있는지 생각해 보기
- `ADMUX = 0x41` 이 ADC1 채널을 뜻한다는 점과 실제 회로 연결을 대응해서 보기
- `ICR1`, `OCR1A` 를 이용한 Timer1 Fast PWM 구조를 손으로 그려 보기

#### `i2c_tempHumi.c`

- SHT20 센서를 I2C(TWI) 로 읽어서 온도와 습도를 LCD에 표시하는 예제이다.
- `SHT2x` 센서 라이브러리와 `TWI_driver` 를 같이 사용하는 구조라서, "센서 드라이버 + 통신 드라이버 + LCD 출력" 이 연결된 형태를 볼 수 있다.
- 온도와 습도를 실수형 계산 결과에서 소수점 한 자리 형태로 가공해서 LCD에 출력하는 부분도 학습 포인트이다.
- 이 예제는 단순 포트 제어를 넘어서, 외부 센서와의 프로토콜 통신을 다루는 단계로 넘어가는 지점이라고 볼 수 있다.

#### 공부 포인트
- I2C/TWI 통신에서 `Init_TWI()` 와 센서 초기화 함수 `SHT2x_Init()` 의 역할 차이 이해하기
- 센서 raw 데이터가 어떻게 실제 온도/습도 값으로 변환되는지 보기
- 에러가 났을 때 `"--.-"` 형태로 대체 표시하는 예외 처리 흐름 익히기

#### `external_eeprom.c`

- SPI 외부 EEPROM(AT25160) 에 문자열을 저장하고, 다시 읽어서 LCD에 출력하는 예제이다.
- `SPI_Init()`, `at25160_Write_Arry()`, `at25160_Read_Arry()` 함수를 통해 "쓰기 -> 읽기 -> 표시" 흐름이 한 파일 안에 정리되어 있다.
- 내부 SRAM 변수만 다루는 것이 아니라, 외부 비휘발성 메모리에 데이터를 저장하는 구조를 연습할 수 있다.
- 같은 문자열 데이터를 주소별로 나눠 저장하는 방식은 메모리 맵 개념을 익히기에도 좋다.

#### 공부 포인트
- SPI EEPROM 에서 왜 주소를 먼저 보내고 그 다음 데이터를 보내는지 생각해 보기
- `0x0100`, `0x0200`, `0x0300` 처럼 구간을 나누는 이유를 정리해 보기
- 전원을 껐다 켜도 남는 메모리와 RAM 의 차이를 이 예제로 연결해서 이해하기

#### `external_eeprom2.c`

- `external_eeprom.c` 에서 미리 저장된 내용을 다시 읽어서 LCD에 출력하는 읽기 중심 예제이다.
- 즉, 한 파일은 "쓰기+읽기", 다른 파일은 "읽기 전용 확인" 용도로 나눠서 실험할 수 있다.
- 저장 동작 없이 바로 읽기만 하기 때문에, EEPROM 에 값이 이미 들어가 있어야 제대로 확인된다는 점도 같이 배울 수 있다.
- 즉, 쓰기 과정과 읽기 과정을 분리해서 보면 SPI 메모리 동작을 더 명확하게 이해할 수 있다.

#### 공부 포인트
- 왜 읽기 전용 테스트 파일을 따로 두면 디버깅이 쉬워지는지 생각해 보기
- EEPROM 에 이전에 저장된 데이터가 실제로 유지되는지 실험으로 확인해 보기
- `lcdPrint((char *)buf3);` 같은 형 변환이 왜 필요한지 자료형 관점에서 이해하기

### 17. PWM, 버저, 통신 추천 학습 흐름

1. `pwmled.c`
2. `pwmbuzzer.c`
3. `buzzermario.c`
4. `dc_pwm_vr.c`
5. `i2c_tempHumi.c`
6. `external_eeprom.c`
7. `external_eeprom2.c`

- 이 순서로 보면 "PWM 출력 -> PWM을 이용한 소리 -> 함수화된 멜로디 -> ADC와 PWM 결합 -> I2C 센서 -> SPI 메모리" 흐름으로 자연스럽게 난이도가 올라간다.
- 즉, 포트 제어와 타이머에서 시작해서 센서와 메모리 같은 외부 장치 통신으로 확장되는 과정을 한 번에 정리할 수 있다.

### 18. CDS 센서 예제 학습 정리

#### `cds.c`

- CDS 조도센서 값을 ADC 로 읽어서 LCD에 표시하고, 동시에 PWM 출력 세기를 조절하는 예제이다.
- 센서 입력값이 단순히 숫자로만 끝나는 것이 아니라, 실제 출력 장치의 동작 변화로 연결된다는 점이 핵심이다.
- ADC 값이 너무 낮거나 높을 때는 각각 최소값과 최대값으로 제한하고, 중간 영역만 비례 계산하는 방식도 들어 있다.
- 즉, 센서 입력을 그대로 쓰기보다 "유효 구간" 을 정해서 제어하는 기초적인 보정 개념을 볼 수 있다.

#### 공부 포인트
- `ADC_result` 가 어떤 방식으로 인터럽트에서 갱신되는지 보기
- `OCR0` 값이 왜 PWM 세기와 직접 연결되는지 Timer0 구조와 함께 이해하기
- `40`, `700`, `255` 같은 상수가 어떤 기준값 역할을 하는지 정리하기

#### `cds2.c`

- `cds.c` 와 거의 같은 구조이지만, ADC 채널을 바꿔서 다른 입력원(예: 다른 센서나 가변저항)을 읽도록 확장한 예제이다.
- LCD 출력 문구도 달라서, 같은 로직을 유지한 채 입력 대상을 바꾸는 연습으로 볼 수 있다.
- 즉, 하나의 ADC 처리 구조를 재사용하면서 채널만 바꾸는 방식이 어떤 의미인지 이해하기 좋다.

#### 공부 포인트
- `ADMUX = 0x40` 과 `ADMUX = 0x41` 차이가 무엇인지 정리하기
- ADC 채널만 달라도 프로그램의 동작 목적이 어떻게 달라질 수 있는지 생각해 보기
- 같은 로직을 복사해서 쓸 때, 어떤 부분은 유지하고 어떤 부분만 바꾸면 되는지 구분하기

#### `cds_fnd.c`

- CDS 센서값을 읽어서 FND 와 LCD 에 함께 표시하는 응용 예제이다.
- 원시 ADC 값은 LCD 에 그대로 보여주고, 사용자가 보기 쉽게 나눈 단계값은 FND 에 표시한다.
- 실제 측정 최대값을 기준으로 보정해서 `0~10` 단계로 압축하는 구조가 들어 있어, "센서값의 시각화" 예제로 보기 좋다.
- 한 자리 FND 에서는 `10` 을 그대로 표현하기 어려워서, 최댓값 단계를 문자 패턴으로 처리하는 점도 실습 포인트이다.

#### 공부 포인트
- 원시값(`ADC value`) 과 구간화된 단계값(`Level`) 의 차이를 명확히 이해하기
- 왜 실제 측정 최대값을 기준으로 다시 보정하면 더 촘촘한 단계 표시가 가능한지 보기
- LCD 와 FND 를 동시에 쓸 때 어떤 정보는 숫자로, 어떤 정보는 단계로 보여주는 것이 더 직관적인지 생각해 보기

### 19. 센서 예제 추천 흐름

1. `cds.c`
2. `cds2.c`
3. `cds_fnd.c`
4. `i2c_tempHumi.c`

- 이 순서로 보면 "단순 ADC 센서 읽기 -> 채널 변경 -> FND/LCD로 시각화 -> I2C 디지털 센서 읽기" 순서로 자연스럽게 확장된다.
- 즉, 아날로그 센서와 디지털 센서의 차이도 함께 비교하면서 학습할 수 있다.

### 20. 모터와 타이머 비교 학습 정리

#### `dc_motor.c`

- DC 모터를 가장 단순한 방식으로 구동하는 예제이다.
- `PD4`, `PD5` 를 번갈아 바꾸면서 모터 회전 방향을 전환하고, `PB5` 를 통해 모터 구동 신호를 켜는 구조이다.
- PWM 없이 단순 ON/OFF 만 사용하므로, 속도 제어보다 "방향 전환" 개념을 먼저 익히는 파일로 볼 수 있다.
- 즉, 모터 제어의 가장 기초가 되는 H-bridge 방향 제어 감각을 익히기 좋다.

#### 공부 포인트
- 왜 방향 제어에 보통 두 개의 핀이 필요한지 생각해 보기
- 모터를 단순히 켜는 것과 방향을 제어하는 것이 어떻게 다른지 정리하기
- LED 제어와 달리 모터는 부하가 큰 장치라는 점을 회로와 함께 보기

#### `dc_pwm.c`

- `dc_motor.c` 에 Timer1 PWM 을 더해서, 모터를 단순 ON/OFF 가 아니라 duty cycle 기반으로 제어하는 예제이다.
- `PB5(OC1A)` 를 PWM 출력으로 설정하고, `ICR1`, `OCR1A` 로 duty 값을 정한다.
- 방향은 여전히 `PD4`, `PD5` 로 제어하고, 속도는 PWM 으로 바꾸는 구조라서 "방향" 과 "속도" 가 분리된다는 점이 중요하다.
- `dc_motor.c` 와 비교해 보면, 같은 모터 제어라도 타이머를 붙이면 제어 수준이 훨씬 올라간다는 것을 이해하기 좋다.

#### 공부 포인트
- `ICR1` 이 PWM 주기를, `OCR1A` 가 duty cycle 을 결정한다는 점 정리하기
- 왜 모터 속도 제어에 단순 지연보다 PWM 이 더 적합한지 생각해 보기
- `dc_motor.c` 와 `dc_pwm.c` 를 나란히 놓고 차이를 표로 정리해 보기

#### `timer1com.c`

- Timer1 비교일치 인터럽트와 overflow 인터럽트를 동시에 사용해서 FND 값을 바꾸는 예제이다.
- `OCR1A`, `OCR1B` 값에 도달했을 때와 overflow 시점마다 ISR 이 호출되며, 그때마다 `time_s` 값이 증가하거나 감소한다.
- 이전 타이머 예제들이 주로 PWM 출력에 초점을 맞췄다면, 이 파일은 "타이머가 특정 시점에 인터럽트를 발생시키는 장치" 라는 면을 보여준다.
- 즉, 타이머를 단순 파형 생성기뿐 아니라 주기적 이벤트 발생기로도 사용할 수 있다는 점을 익히기 좋다.

#### 공부 포인트
- compare match 와 overflow 인터럽트의 차이를 명확히 구분하기
- `TIMSK` 에서 어떤 비트를 켜야 어떤 ISR 이 동작하는지 정리하기
- ISR 에서 값만 바꾸고, 메인 루프에서는 표시만 담당하는 구조를 다른 예제와 비교해 보기

### 21. 모터와 타이머 추천 흐름

1. `dc_motor.c`
2. `dc_pwm.c`
3. `dc_pwm_vr.c`
4. `timer1com.c`

- 이 순서로 보면 "모터 단순 구동 -> PWM 속도 제어 -> ADC와 결합한 가변 속도 제어 -> Timer1 인터럽트 응용" 흐름으로 확장된다.
- 즉, 타이머를 PWM 용도로 쓰는 경우와 인터럽트 발생 용도로 쓰는 경우를 함께 비교해 볼 수 있다.
