#include <iostream>

using namespace std;

int rec_func(int n);

int sum = 0;

int main(void){
    cout << rec_func(10) << endl;
    return 0;
}


int rec_func(int n){
    if(n == 0)
        return sum;
    sum += n;
    rec_func(n-1);
}

