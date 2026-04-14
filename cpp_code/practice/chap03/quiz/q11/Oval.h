#pragma once
#include <iostream>

class Oval{
private:
    int width, height;
public:
    int getWidth();
    int getHeight();
    void set(int w, int h);
    void show();
    double area();

    Oval();
    Oval(int w, int h);
    ~Oval();
};