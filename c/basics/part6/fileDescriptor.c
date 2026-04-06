#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){

    int fd;
    char *path = "/home/asd/study/c/basics/part6";
    char fPath[100];
    sprintf(fPath, "%s%s",path,"/test.dat"); //sprintf() 함수를 사용하여 파일 경로를 생성합니다. fPath 배열에 path와 "/test.dat"를 결합하여 완전한 파일 경로를 만듭니다.
    fd = open(fPath, O_WRONLY | O_CREAT | O_TRUNC, 0644); //파일이 없으면 생성, 있으면 덮어쓰기 //비트연산자 |는 OR연산자, 0644는 권한
    if(fd == -1) // 파일 열기에 실패했을 때 
        printf("파일을 열수 없다.\n");
    write(fd, " 이것은 파일로 저장되는 예시 데이터 입니다!",62);
    close(fd);
    return 0;

 } //버퍼가 없이 파일에 직접 데이터를 쓰는 예시입니다. open() 함수로 파일을 열고, write() 함수로 데이터를 쓰며, 마지막으로 close() 함수로 파일을 닫습니다. 버퍼가 없이 직접 파일에 데이터를 쓰는 경우, 데이터가 즉시 파일에 기록됩니다. 이 방법은 버퍼링이 필요 없는 간단한 파일 작업에 적합합니다. 하지만 대량의 데이터를 처리하거나 성능이 중요한 경우에는 버퍼링을 사용하는 것이 좋습니다. 버퍼링을 사용하면 데이터를 메모리에 임시로 저장한 후 한 번에 파일에 기록하므로, 디스크 I/O 횟수를 줄여 성능을 향상시킬 수 있습니다.
