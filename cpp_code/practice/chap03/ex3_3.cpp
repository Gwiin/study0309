#include <iostream>
using namespace std;


//Circle 클래스 선언=============
class Circle{
public:
    //멤버변수
    int radius;
    //멤버함수
    double getArea(void);

    //생성자 함수 선언
    Circle();
    Circle(int r);
};

//Circle 멤버함수 getArea() 구현
double Circle::getArea(void){
    return 3.14*radius*radius;
}

//Circle 생성자 함수 구현
Circle::Circle(){ // 매개변수 없는 생성자 함수 구현
    radius = 1;
    cout << "반지름" << radius << " 원 생성" << endl;
}

Circle::Circle(int r){ // 매개변수 있는 생성자 함수 구현
    radius = r;
    cout << "반지름" << radius << " 원 생성" << endl;
}



//main 함수 구현====================
int main(void){

    Circle donut;
    double area = donut.getArea();
    cout << "donut 면적은 " << area << endl;

    Circle pizza(30);
    area = pizza.getArea();
    cout << "pizza 면적은 " << area << endl;
    

    return 0;
}
