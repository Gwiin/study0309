#include <iostream>
using namespace std;

class Cube{
private:
    //가로 세로 높이 변수
    int width;
    int length;
    int height;

public:
    int getVolume(); //부피 계산해서 리턴
    void increase(int in_w, int in_l, int in_h); //가로 세로 높이 증가값 받아 계산
    bool isZero(); //부피가 0이면 true, 0이 아니면 false 리턴

    Cube(int w, int l, int h);
};

int Cube::getVolume(){
    return width*length*height;
} //부피 계산해서 리턴

void Cube::increase(int in_w, int in_l, int in_h){
    width += in_w;
    length += in_l;
    height += in_h;
} //가로 세로 높이 증가값 받아 계산

bool Cube::isZero(){
    if((width*length*height) == 0)
        return true;
    else
        return false;

} //부피가 0이면 true, 0이 아니면 false 리턴

Cube::Cube(int w, int l, int h){
    width = w;
    length = l;
    height = h;
}


//====================================================================
//====================================================================
int main(){
    Cube cube(1,2,3);
    cout << "큐브의 부피는 " << cube.getVolume() << endl;
    cube.increase(1,2,3);
    cout << "큐브의 부피는 " << cube.getVolume() << endl;
    if(cube.isZero()) cout << "큐브의 부피는 0" << endl;
    else cout << "큐브의 부피는 0이 아님" << endl;

    return 0;
}

