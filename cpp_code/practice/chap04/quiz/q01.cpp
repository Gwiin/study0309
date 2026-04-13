#include <iostream>
using namespace std;



int main(){

    double *temp  = new double(5);
    double sum = 0;

    cout << "온도 5개 입력>> ";
    for(int i = 0; i < 5 ; i++){
        cin >> *(temp+i);
    }

    for(int i = 0 ; i < 5 ; i++){
        sum += *(temp+i);
    }
    cout << "평균은 " << sum/5.0 << endl;
    
    delete temp;
    return 0;
}