#include <stdio.h>

int main(void){

    char ch;
    char str[100];

    printf("문자를 입력하세요: ");
    ch = getc(stdin);
    //ch = fgetc(stdin);
    ch = getchar(); //getc와 fgetc는 stdin에서 문자를 읽어오는 함수입니다. getchar는 getc(stdin)과 동일한 기능을 수행하는 함수입니다. 따라서, getchar()를 사용하여 stdin에서 문자를 읽어올 수 있습니다.
    printf("%d %d %d",stdin->_fileno,stdout->_fileno,stderr->_fileno);

    printf("입력한 문자는 %c 입니다.\n", ch);


    while(getchar()!='\n'); //입력 버퍼에 남아있는 개행 문자를 제거하는 역할을 합니다. 사용자가 입력한 문자를 읽은 후, 입력 버퍼에는 개행 문자가 남아있을 수 있습니다. 이 개행 문자는 다음 입력에서 문제가 될 수 있으므로, while 루프를 사용하여 개행 문자가 나올 때까지 getchar()를 호출하여 입력 버퍼를 비우는 것입니다.
    ch = fgetc(stdin);
    printf("입력한 문자는 %c 입니다.\n",ch);
    scanf("%s",str);
    printf("입력한 문자열은 %s 입니다.\n",str);

    return 0;
}