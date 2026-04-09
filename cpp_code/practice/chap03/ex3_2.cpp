#include <iostream>
using namespace std;


//Rectangle 클래스 선언=============
class Rectangle{
public:
    int width;
    int height;

    int getArea(void);
};

//Rectangle 멤버함수 getArea() 구현
int Rectangle::getArea(void){
    return width*height;
}

//main 함수 구현====================
int main(void){

    Rectangle rect; //Rectangle 클래스의 rect 오브젝트 생성
    rect.width = 3;
    rect.height = 5;
    cout << "사각형의 면적은 " << rect.getArea() << endl;

    return 0;
}
