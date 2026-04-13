#include <string>
#include <iostream>
using namespace std;


string str_append(string str1, char *str2){
    str1 = str1 + str2;
    return str1;
}

int main(){
    string str = "I love ";
    str = str_append(str,"C++");
    cout << str << endl;

    string str2("test", 3);
    cout << str2 << endl;
    cout << str2[1] << endl;
    return 0;
}
