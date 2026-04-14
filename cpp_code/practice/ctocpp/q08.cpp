#include <iostream>
#include <string>
using namespace std;


int main(void){
    string line;
    int cnt = 0;

    cout << "문장 입력 : " ;
    getline(cin, line, '\n');

    int size = line.size();
    
    for(int i = 0 ; i < size ; i++){
        if(line[i] > 64 && line[i] < 91){
            line[i] = line[i] + 32;
            cnt++;
        }
    }

    cout << "바뀐 문장 : " << line << endl;
    cout << "바뀐 문자 수 : " << cnt << endl;
    return 0;
}