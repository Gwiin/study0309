#include <iostream>
#include <string>
using namespace std;

string multiString(int n);


class Coffee
{
private:
    int coffee;
    int sugar;
    int milk;
    int water;

public:
    void show();

    Coffee();
    Coffee(int co, int su, int mi, int wa);
};

void Coffee::show(){
    cout << "coffee " << multiString(coffee) << endl;
    cout << "sugar " << multiString(sugar) << endl;
    cout << "milk " << multiString(milk) << endl;
    cout << "water " << multiString(water) << endl;
}

Coffee::Coffee(){
    coffee = 10;
    sugar = 0;
    milk = 0;
    water = 0;
}

Coffee::Coffee(int co, int su, int mi, int wa){
    coffee = co;
    sugar = su;
    milk = mi;
    water = wa;
}



int main(){
    Coffee espresso;
    Coffee americano(5,0,0,10);
    Coffee cappucchino(5,1,5,2);
    Coffee mySweet(3,7,5,5);

    espresso.show();
    cout << endl;
    mySweet.show();
}

string multiString(int n){
    string st;
    for (int i=0; i<n; i++){
        st += "*";
    }
    return st;
}