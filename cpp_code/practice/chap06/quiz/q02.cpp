#include <iostream>
using namespace std;

void printMatrix(int a=2, int b=2, char c='*');

int main(void){
    printMatrix();
    printMatrix(2, 5, 'a');
    printMatrix(1, 10);
}

void printMatrix(int a, int b, char c){
    for(int i = 0 ; i < a ; i++){
        for(int j = 0 ; j < b ; j++){
            cout << c;
        }
        cout << endl;
    }
}

