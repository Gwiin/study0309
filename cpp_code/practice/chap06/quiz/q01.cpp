#include <iostream>

using namespace std;

int add(int a[], int b, int c = 0);

int main(void){
    int a[] = { 1,2,3,4,5 };
    int b[] = { 6,7,8,9,10 };
    int c = add(a, 5);
    int d = add(b, 3, c);
    cout << c << endl;
    cout << d << endl;

    return 0;
}


int add(int a[], int b, int c){
    int sum = 0;
    for(int i = 0 ; i < b ; i++){
        sum += a[i];
    }
    sum += c;

    return sum;
}

