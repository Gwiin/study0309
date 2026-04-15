#include <iostream>

using namespace std;

class Color{
private:
    int r, g, b;
public:
    Color(int r, int g, int b);

    void get(int &r, int &g, int &b);

};

Color::Color(int r, int g, int b){
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::get(int &r, int &g, int &b){
    r = this->r;
    g = this->g;
    b = this->b;
}

int main(void){

    Color fore(255, 0, 0), back(15, 128, 200);
    int r, g, b;
    fore.get(r, g, b);
    cout << "red=" << r << ", green=" << g << ", blue=" << b << endl;
    back.get(r, g, b);
    cout << "red=" << r << ", green=" << g << ", blue=" << b << endl;

    return 0;
}