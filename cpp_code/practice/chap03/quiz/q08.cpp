#include <iostream>
#include <string>

using namespace std;

class Calculator{
private:
    int value;
    void calc(string op, int number);
public:
    Calculator();
    int getValue();
    void loop();
};

Calculator::Calculator(){
    this->value = 0;
}

void Calculator::calc(string op, int number){
    
    if(op == "+"){
        value = value + number;
    }
    else if(op == "-"){
        value = value - number;
    }
    else if(op == "*"){
        value = value * number;
    }
    else if(op == "/"){
        if(number == 0){}
        else {
            value = value / number;
        }
    }
}

int Calculator::getValue(){
    return value;
}

void Calculator::loop(){
    string oper;
    int num;

    while(1){
        
        cout << "연산 입력>>";
        cin >> oper >> num;
        if(oper == "그만")
            break;
        calc(oper, num);
    }
}

int main(void){
    Calculator jane;
    jane.loop();
    cout << "연산 결과는 " << jane.getValue() << endl;

    return 0;
}
