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


void addBubble(Bubble &c_bu, Bubble &a_bu, Bubble &b_bu);

int main(){
    Bubble a(5), b(10), c(130);
    addBubble(c, a, b);
    cout << "버블 c의 반지름 " << c.getRadius() << endl;
    
    return 0;
}

void addBubble(Bubble &c_bu, Bubble &a_bu, Bubble &b_bu){
    int r = c_bu.getRadius() + a_bu.getRadius() + b_bu.getRadius();
    c_bu.setRadius(r);
}