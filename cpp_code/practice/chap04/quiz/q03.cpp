#include <iostream>
#include <string>
using namespace std;


int main(){

    string dest;
    string line;

    cout << "텍스트 입력>>";
    getline(cin, line, '\n');

    int size = line.size();
    
    for(int i = 0; i < size ; i++){
        if(line[i] == ' ' && line[i+1] != ' '){
            dest.append(1,' ');
        }
        else if(line[i] != ' '){
            dest.append(1,line[i]);
        }
    }
    cout << dest << endl;

    return 0;
}