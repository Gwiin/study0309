#include <iostream>
using namespace std;


//Rectangle 클래스 선언=============
class Rectangle{
public:
    int width;
    int height;

    int getArea(void);

    Rectangle();
    Rectangle(int w);
    Rectangle(double h);
    Rectangle(int w, int h);
};

//Rectangle 멤버함수 getArea() 구현
int Rectangle::getArea(void){
    return width*height;
}

//Rectangle 생성자 함수 구현
// Rectangle::Rectangle(){
//     width = 1;
//     height = 1 ;
//     cout << "WIDTH = " << width << " HEIGHT = " << height << " 인 사각형 생성" << endl;
// }

Rectangle::Rectangle() : Rectangle(1,1){} //위임생성자

Rectangle::Rectangle(int w){
    width = w;
    height = 1 ;
    cout << "WIDTH = " << width << " HEIGHT = " << height << " 인 사각형 생성" << endl;
}  

Rectangle::Rectangle(double h){
    width = 1;
    height = (int)h ;
    cout << "WIDTH = " << width << " HEIGHT = " << height << " 인 사각형 생성" << endl;
}  

Rectangle::Rectangle(int w, int h){
    width = w;
    height = h ;
    cout << "WIDTH = " << width << " HEIGHT = " << height << " 인 사각형 생성" << endl;
}




//main 함수 구현====================
int main(void){

    Rectangle rect1;
    cout << "사각형의 면적은 " << rect1.getArea() << endl;
    Rectangle rect2(20);
    cout << "사각형의 면적은 " << rect2.getArea() << endl;
    Rectangle rect3(20,40);
    cout << "사각형의 면적은 " << rect3.getArea() << endl;
    Rectangle rect4(5.0);

    //rect3.Rectangle(30,30); XXXXX
    rect3 = Rectangle(30,30);

    return 0;
}
