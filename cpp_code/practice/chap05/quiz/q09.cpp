#include <iostream>

using namespace std;

class MyStack
{
private:
    int p[10];
    int tos = 0;
public:
    MyStack();

    bool push(int n);
    bool pop(int &n);

};

MyStack::MyStack(){
    for (int i = 0 ; i < 10 ; i++){
        p[i] = 0;
    }
}

bool MyStack::push(int n){
    if (this->tos != 10){
        p[this->tos] = n;
        this->tos++;
        return true;
    }
    else{
        return false;
    }
}

bool MyStack::pop(int &n){
    if(this->tos > 0){
        this->tos--;
        n = p[this->tos];
        return true;
    }
    else{
        return false;
    }
}



int main(void){
    MyStack st;
    for (int i = 0; i < 11; i++){
        if(st.push(i)) cout << i << ' ';
        else cout << endl << i+1 << "번째 푸시 실패! 스택 차 있음" << endl;
    }

    int n;
    for (int i = 0; i < 11 ; i++){
        if (st.pop(n)) cout << n << ' ';
        else cout << endl << i+1 << "번째 팝 실패! 스택이 비어 있음" << endl;
    }
}
