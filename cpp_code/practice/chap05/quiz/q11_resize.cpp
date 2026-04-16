#include <iostream>

using namespace std;

class MyStack
{
private:
    int *p;
    int size = 0;
    int tos = 0;
public:
    MyStack();
    MyStack(int size);
    MyStack(const MyStack &src);
    ~MyStack();

    bool push(int n);
    bool pop(int &n);
};

MyStack::MyStack(){
}

MyStack::MyStack(int size){
    this->p = new int [size];
    for (int i = 0 ; i < size ; i++){
        this->p[i] = 0;
    }
}

MyStack::MyStack(const MyStack &src){
    this->size = src.size;
    this->tos = src.tos;
    this->p = new int [this->size];
    for (int i = 0; i < this->tos ; i++){
        this->p[i] = src.p[i];
    }
}

MyStack::~MyStack(){
    if(p){
        cout << "할당 해제" << endl;
        delete [] p;
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
    MyStack a(10);
    a.push(10);
    a.push(20);

    MyStack b = a;
    b.push(30);

    int n;
    a.pop(n);
    cout << "스택 a에서 팝한 값 " << n << endl;
    b.pop(n);
    cout << "스택 b에서 팝한 값 " << n << endl;
}
