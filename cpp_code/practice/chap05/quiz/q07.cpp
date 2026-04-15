#include <iostream>

using namespace std;

class Power{
private:
    int kick, punch;
public:
    Power(int kick, int punch);
    Power &add(Power p);
    void show();
};

Power::Power(int kick, int punch){
    this->kick = kick;
    this->punch = punch;
}

Power &Power::add(Power p){
    this->kick += p.kick;
    this->punch += p.punch;

    return *this;
}


void Power::show(){
    cout << "kick=" << this->kick << ", punch=" << punch << endl;
}


int main(void){
    Power a(1, 2), b(10, 20), c(100, 200);
    c.add(a).add(b).add(Power(1000,2000));
    c.show();
}

