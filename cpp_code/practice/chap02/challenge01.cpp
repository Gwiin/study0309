#include <iostream>
#include <string>
using namespace std;

int main(){
    string s,t;
    
    cout << "가위 바위 보 게임을 합니다. 가위, 바위, 보 중에서 입력하세요." << endl;
    
    cout << "로미오>>";
    cin >> s;
    cout << "줄리엣>>";
    cin >> t;

    if((s == "가위" && t == "보")||(s == "바위" && t == "가위")||(s == "보" && t == "바위"))
        cout << "로미오가 이겼습니다." << endl;
    else if((s == "바위" && t == "보")||(s == "보" && t == "가위")||(s == "가위" && t == "바위"))
        cout << "줄리엣이 이겼습니다." << endl;
    else
        cout << "비겼습니다." << endl;

    return 0;
}