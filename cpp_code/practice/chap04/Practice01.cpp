#include <iostream>
using namespace std;

//클래스=============================================================================
class myArray{
private:
    int *p;
    int arysize;

public:
    myArray* this_point(){return this;};
    int sum();
    void print();

    myArray(int num);
    ~myArray();

};

    //멤버함수
int myArray::sum(){ //합
    int p_sum = 0;
    for(int i = 0 ; i < arysize ; i++){
        p_sum += p[i];
    }
    return p_sum;
}

void myArray::print(){ //출력
    for(int i = 0; i<arysize ; i++){
        cout << "p[" << i << "] = " << *(p+i) << endl;
    }
}

    //생성자
myArray::myArray(int num){
    arysize = num;
    if(p){
        p = new int [arysize];
        cout << "메모리 할당 성공" << endl;
    }
    
}

    //소멸자
myArray::~myArray(){
    delete [] p;
    cout << "메모리 할당 해제" << endl; 
}


//main==============================================================================
int main(){
    myArray test[3] = {myArray(3), myArray(4), myArray(5)};

    myArray* p = test[0].this_point();


    // int tmp = 1;
    // for(int i = 0 ; i<3;i++){
    //     for(int j = 0; j < test[i].arysize ; j++){
    //         test[i].p[j] = tmp++;
    //         cout << test[i].p[j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

   // cout << "a의 총합은 " << a.sum() << endl; 

    return 0;
}