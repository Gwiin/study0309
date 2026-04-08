#include <iostream>
using namespace std;


void my_strcat(const char *f, const char *s, char *fs_cat);

int main(){
    //배열 선언, 초기화
    char f_name[10] = {0};
    char s_name[10] = {0};
    char fs_name[20] = {0};

    
    cout << "첫번째 이름을 입력 : "; 
    cin >> f_name;
    cout << "두번째 이름을 입력 : ";
    cin >> s_name;

    my_strcat(f_name, s_name, fs_name);
    
    cout << "전 체 이름 출력 : " << fs_name << endl;
    return 0;
}


void my_strcat(const char *f_cat, const char *s_cat, char *fs_cat){

    int last_index = 0;

    for (int i=0; i < 10; i++){
        if(f_cat[i] != '\0')
            fs_cat[i] = f_cat[i];
        else{
            fs_cat[i] = '\0'; 
            last_index = i;
            break;
        }
    }

    for (int i = 0 ; i < 10 ; i++){
        if(s_cat[i] != '\0')
            fs_cat[last_index+i] = s_cat[i];
        else{
            fs_cat[last_index+i] = '\0';
            break;
        }
    }


}
