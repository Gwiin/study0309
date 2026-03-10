#include <stdio.h>
#include <string.h>

int main()
{
    char fruit[20] = "strawberry";
    printf("딸기 : %s\n", fruit);
    printf("딸기잼 : %s %s\n", fruit, "jam");
    strcpy(fruit, "banana");
    printf("바나나 : %s\n", fruit);
    // strcpy fruit -> apple
    fruit[0] = 'a';
    printf("사과 : %s\n", fruit); 
    fruit[0] = 'p';
    printf("사과 : %s\n", fruit); 
    fruit[0] = 'p';
    printf("사과 : %s\n", fruit); 
    fruit[0] = 'l';
    printf("사과 : %s\n", fruit);
    fruit[0] = 'e';
    printf("사과 : %s\n", fruit); 
    return 0;
}