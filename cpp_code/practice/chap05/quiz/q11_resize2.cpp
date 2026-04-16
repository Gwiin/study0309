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

    void resize(int size);

    bool push(int n);
    bool pop(int &n);
    
    int getSize() { return size; }
    int getTos() { return tos;}
    void show();
};

MyStack::MyStack(){
}

MyStack::MyStack(int size){
    this->size = size;
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


void MyStack::resize(int size){
    int *tmp = new int [size];
    cout << "새로운 확장 공간 할당" << endl;
    this->size = size;
    for (int i = 0; i < this->tos ; i++){
        tmp[i] = this->p[i];
    }
    for(int i = this->tos ; i < this->size ; i++){
        tmp[i] = 0;
    }
    delete [] p;
    cout << "이전 공간 해제" << endl;
    this->p = tmp;
}


void MyStack::show(){
    for(int i = 0 ; i < this->size ; i++){
        cout << this->p[i] << " ";
    }
    cout << endl;
}


bool MyStack::push(int n){
    if (this->tos != this->size){
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

    a.resize(20);
    for(int i = a.getTos() ; i < a.getSize() ; i++){
        a.push(i);
    }
    a.show();

    return 0;
}
