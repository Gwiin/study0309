#include <iostream>
using namespace std;

char *my_strcat(const char *str1, const char *str2); //함수 선언


//=======================================================================
//=============================main======================================

int main(){
    //배열 선언, 초기화
    char f_name[10] = {0};
    char s_name[10] = {0};
    // char fs_name[20] = {0};

    
    cout << "첫번째 이름을 입력 : "; 
    cin >> f_name;
    cout << "두번째 이름을 입력 : ";
    cin >> s_name;

    char *fs_name = my_strcat(f_name, s_name);
    
    cout << "전 체 이름 출력 : " << fs_name << endl;

    free(fs_name); //동적할당해제
    return 0;
}

//=======================================================================
//========================my_strcat======================================

char *my_strcat(const char *str1, const char *str2){

    int temp = 0;
    char *str3 = (char*)malloc(sizeof(char)*20); //동적할당

    for (int i=0; i < 10; i++){
        if(str1[i] != '\0')
            str3[i] = str1[i];
        else{
            str3[i] = '\0'; 
            temp = i;
            break;
        }
    }

    for (int i = 0 ; i < 10 ; i++){
        if(str2[i] != '\0')
            str3[temp+i] = str2[i];
        else{
            str3[temp+i] = '\0';
            break;
        }
    }
    return str3;
}
