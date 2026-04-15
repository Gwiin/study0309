#include <iostream>
using namespace std;

class Bubble{
private:
    int radius;
public:
    Bubble(int radius) { this->radius = radius; }

    int getRadius() { return radius; }
    void setRadius(int n) { radius = n; }
};

bool combineBubble(Bubble &a, Bubble &b);

int main(){
    Bubble a(5), b(10);
    if(combineBubble(a,b) == false)
        cout << "두 버블의 크기가 같음" << endl;
    else
        cout << "큰 쪽으로 병합됨 " << endl;
    cout << "버블 a의 반지름 " << a.getRadius() << endl;
    cout << "버블 b의 반지름 " << b.getRadius() << endl;
    
    return 0;
}


bool combineBubble(Bubble &a, Bubble &b){
    int a_n = a.getRadius();
    int b_n = b.getRadius();
    if(a_n > b_n){
        a.setRadius(a_n+b_n);
        b.setRadius(0);
        return true;
    }
    else if(a_n < b_n){
        b.setRadius(a_n+b_n);
        a.setRadius(0);
        return true;
    }
    else
        return false;
}
