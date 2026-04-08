#include <iostream>
using namespace std;

void my_StrCat(char *f_name, char *s_name, char *fs_name);

int main(){

    char f_name[10] = {0};
    char s_name[10] = {0};
    char fs_name[20] = {0};

    cout << "첫번째 이름을 입력 : "; 
    cin >> f_name;
    cout << "두번째 이름을 입력 : ";
    cin >> s_name;

    my_StrCat(f_name,s_name,fs_name);


    cout << "전 체 이름 출력 : " << fs_name << endl;
    return 0;
}


void my_StrCat(char *f_name, char *s_name, char *fs_name)
{

    int count = 0;
    int i =0;
    while(1){
        if(f_name[i] == 0)
            break;
        fs_name[count] = f_name[i];
        i++;
        count++;

    } 
    i = 0;
    while(1){
        if(s_name[i] == '\0'){
            fs_name[count] = s_name[i];
            break;
        }
        fs_name[count] = s_name[i];
        i++;
        count++;
    }

}


// void my_StrCat(char *f_name, char *s_name, char *fs_name)
// {

//     int count = 0;
//     int i =0;
//     while(1){
//         if(f_name[i] == 0)
//             break;
//         fs_name[count] = f_name[i];
//         i++;
//         count++;

//     } 
//     i = 0;
//     while(1){
//         if(s_name[i] == '\0'){
//             fs_name[count] = s_name[i];
//             break;
//         }
//         fs_name[count] = s_name[i];
//         i++;
//         count++;
//     }

// }