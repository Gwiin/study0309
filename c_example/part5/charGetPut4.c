#include <stdio.h>
#include <unistd.h>

int main(void){

    char ch = 'a';

    printf("program start\n");
    putchar(ch);
    fflush(stdout);
    sleep(1);
    printf("putchar 실행 후\n"); 
    putc(ch,stdout); //file stream 지정
    fflush(stdout);
    sleep(1);

    char *string1 = "스트링1 배열입니다.";
    puts(string1); //putchar와 달리 자동으로 줄바꿈이 된다.
    sleep(1);
    printf("puts 실행 후 ");
    fputs(string1,stdout);
    sleep(1);
    printf("프로그램 끝");
    return 0;
} //putchar, putc 는 버퍼에 저장하기 때문에 바로 출력되지 않을 수 있다. fflush(stdout)로 버퍼를 비워준다.