#include <iostream>
#include <string>
using namespace std;


string my_strcat(const string str1, const string str2);

int main(){
    string f_name;
    string s_name;
    string fs_name;

    
    cout << "첫번째 이름을 입력 : "; 
    getline(cin,f_name);
    cout << "두번째 이름을 입력 : ";
    getline(cin,s_name);

    fs_name = my_strcat(f_name, s_name);
    
    cout << "전 체 이름 출력 : " +  fs_name << endl;
    return 0;
}


string my_strcat(const string str1, const string str2){
    // string str3;
    // str3 = str1+str2;
    return str1+str2;
}
