#include <iostream>
#include <string>
using namespace std;

class Pipe{
private:
    int data[10];
    int index;
public:
    Pipe();

    int arrive(int n);
    int shift();
    void show();
};

Pipe::Pipe(){
    for(int i = 0 ; i < 10 ; i++){
        data[i] = 0;
    }
    index = 0;
}

int Pipe::arrive(int n){
    int tmp;
    if(index == 10){
        tmp = data[0];
        for (int i = 0; i < 9 ; i++){
            data[i] = data[i+1];
        }
        data[9] = n;
        return tmp;
    }
    else{
        data[index] = n;
        index++;
        return -1;
    }
}

int Pipe::shift(){
    int tmp = data[0];
    for(int i = 0 ; i < 9 ; i++){
        data[i] = data[i+1];
    }
    data[9] = 0;
    //index--;
    return tmp;
}

void Pipe::show(){
    cout << "파이프 내부 [";
    for(int i = 0 ; i < 10 ; i++){
        cout << data[i] << " ";
    }
    cout << "\b]" << endl;
}


int main(void){
    Pipe pipe;
    for(int i = 0; i < 6; i++){
        pipe.arrive(i);
    }
    pipe.show();
    for(int i = 6; i < 12; i++){
        pipe.arrive(i);
    }
    pipe.show();

    int front = pipe.shift();
    cout << "shift()로 제거된 맨 앞 데이터 : " << front << endl;
    pipe.show();
    front = pipe.arrive(50);

    cout << "arrive(50)로 제거된 맨 앞 데이터 : " << front << endl;
    pipe.show();

    return 0;
}