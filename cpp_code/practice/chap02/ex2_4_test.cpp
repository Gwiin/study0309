#include <iostream>
using namespace std;

int main(){
    //배열 선언, 초기화
    char f_name[10] = {0};
    char s_name[10] = {0};
    char fs_name[20] = {0};

    
    cout << "첫번째 이름을 입력 : "; 
    cin >> f_name;
    cout << "두번째 이름을 입력 : ";
    cin >> s_name;

    int last_index = 0;


    for (int i=0; i < 10; i++){
        if(f_name[i] != '\0')
            fs_name[i] = f_name[i];
        else{
            fs_name[i] = '\0'; 
            last_index = i;
            break;
        }
    }

    for (int i = 0 ; i < 10 ; i++){
        if(s_name[i] != '\0')
            fs_name[last_index+i] = s_name[i];
        else{
            fs_name[last_index+i] = '\0';
            break;
        }
    }

    
    cout << "전 체 이름 출력 : " << fs_name << endl;
    return 0;
}



