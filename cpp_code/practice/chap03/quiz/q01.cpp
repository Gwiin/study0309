#include <iostream>
#include <string>
using namespace std;

//클래스선언============================================
class Picture
{
private:
    int width;
    int height;
    string mountain;

public:
    int getWidth();
    int getHeight();
    string getPlace();

    Picture();
    Picture(int w, int h, string mt);

};

    //멤버함수=========================
int Picture::getWidth(){
    return width;
}

int Picture::getHeight(){
    return height;
}

string Picture::getPlace(){
    return mountain;
}

    //생성자===========================
Picture::Picture()
{  
    width = 5;
    height = 7;
    mountain = "모름";
}

Picture::Picture(int w, int h, string mt){
    width = w;
    height = h;
    mountain = mt;
}


//main함수=======================================================
int main(){
    Picture pic;
    Picture mt(10,14,"한라산");
    cout << pic.getWidth() << "x" << pic.getHeight() << " " << pic.getPlace() << endl;
    cout << mt.getWidth() << "x" << mt.getHeight() << " " << mt.getPlace() << endl;

}