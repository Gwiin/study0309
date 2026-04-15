#include <iostream>
using namespace std;

void twice(int &a);

int main(void){

    int n = 12;
    twice(n);
    cout << n << endl;

    return 0;
}

void twice(int &a){
    a *= 2;

}