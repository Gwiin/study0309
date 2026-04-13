#include <iostream>
#include <string>
using namespace std;

int main(){

    string line;
    string dest;

    cout << "텍스트 입력(한글 안 됨)>>";
    getline(cin, line, '\n');
    int size = line.size();

    for(int i = 0; i < size ; i++){
        if( (isalpha(line[i])) || line[i] == ' ' ){
            dest.append(1,line[i]);
        }
    }
    cout << dest << endl;

    return 0;
}