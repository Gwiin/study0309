#include <iostream>

using namespace std;

class CoffeMachine{
private:
//커피 물 설탕
    int coffee;
    int water;
    int sugar;
    
public:
    void drinkEspresso(); // 커피 1, 물 1 소비
    void drinkAmericano(); // 커피 1, 물 2 소비
    void drinkSugarCoffee(); // 커피 1, 물 2, 설탕 1 소비
    void fill(); // 커피 10, 물 10, 설탕 10 채우기
    void show(); // 현재 커피 머신 상태 출력

    CoffeMachine(int c, int w, int s);
};

    //멤버함수==============================================================
void CoffeMachine::drinkEspresso(){ // 커피 1, 물 1 소비
    coffee -= 1;
    water -= 1;
} 

void CoffeMachine::drinkAmericano(){    // 커피 1, 물 2 소비
    coffee -= 1;
    water -= 2;
} 

void CoffeMachine::drinkSugarCoffee(){  // 커피 1, 물 2, 설탕 1 소비
    coffee -= 1;
    water -= 2;
    sugar -= 1;
} 

void CoffeMachine::fill(){  // 커피 10, 물 10, 설탕 10 으로 채우기
    coffee = 10;
    water = 10;
    sugar = 10;
} 

void CoffeMachine::show(){  // 현재 커피 머신 상태 출력
    cout << "[머신 상태] 커피:" << coffee << "\t물:" << water << "\t설탕:" << sugar << endl; 
} 

    //생성자=============================================================
CoffeMachine::CoffeMachine(int c, int w, int s){
    coffee = c;
    water = w;
    sugar = s;
}

//=========================================================================================================================
//main=====================================================================================================================
int main(){
    CoffeMachine java(5,10,6);
    java.drinkEspresso();
    java.show();
    java.drinkAmericano();
    java.show();
    java.drinkSugarCoffee();
    java.show();
    java.fill();
    java.show();

    return 0;
}