#include <iostream>
#include "Oval.h"
using namespace std;

int Oval::getWidth(){
    return width;
}
int Oval::getHeight(){
    return height;
}
void Oval::set(int w, int h){
    width = w;
    height = h;
}
void Oval::show(){
    cout << "Oval: width=" << width << ", height=" << height << endl;
}
double Oval::area(){
    return 3.14*width*height/4;
}

Oval::Oval(){
    width = 1;
    height = 1;
}

Oval::Oval(int w, int h){
    width = w;
    height = h;
}

Oval::~Oval(){
    cout << "Oval 소멸: " << width << "x" << height << endl;
}

