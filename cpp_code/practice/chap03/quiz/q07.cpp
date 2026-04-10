#include <iostream>

using namespace std;

class Storage{
private:
    //변수
    double data[10];
    int next;

public:
    //함수
    void put(double temp);
    void dump();
    double getAvg();
    //생성자
    Storage();
};

//함수 구현
void Storage::put(double temp){
    data[next] = temp;
    next++;
}

void Storage::dump(){
    for(int i=0 ; i < next ; i++){
        cout << data[i] << " ";
    }
    cout << endl;
}

double Storage::getAvg(){
    double sum= 0.0;
    for (int i=0; i < next ; i++){
        sum += data[i];
    }
    return sum / (double)next;
}

//생성자 함수 구현
Storage::Storage(){
    for(int i=0; i<10 ; i++){
        data[i] = 0;
    }
    next = 0;
}

//메인 함수 구현
int main(){
    Storage a;
    a.put(36.7);
    a.put(36.9);
    a.put(36.4);
    a.dump();
    cout << "평균 체온은 " << a.getAvg() << "입니다." << endl;
}