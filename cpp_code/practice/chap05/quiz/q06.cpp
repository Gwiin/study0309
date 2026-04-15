#include <iostream>

using namespace std;

class Polygon{
private:
    int size = 0;
    int *xList, *yList;
public:
    Polygon(int size);
    ~Polygon();

    void read();
    bool get(int n, int &x, int &y);
};

Polygon::Polygon(int size){
    this->size = size;
    xList = new int [size];
    yList = new int [size];
}

Polygon::~Polygon(){
    delete [] xList;
    delete [] yList;
}

void Polygon::read(){
    cout << "아래에 x, y 값으로 6개의 점을 입력하세요." << endl;
    for(int i = 0 ; i < size ; i++){
        cin >> xList[i] >> yList[i];
    }
}

bool Polygon::get(int n, int &x, int &y){
    if( (n < 1) || (n > size) ){
        return false;
    }
    else{
        x = xList[n-1];
        y = yList[n-1];
        return true;
    }
}



int main(void){
    Polygon poly(6);
    poly.read();
    int n = 3, x, y;
    bool res = poly.get(n, x, y);

    if(res == true)
        cout << n << "번째 점은 " << "(" << x << ", " << y << ")" << endl;
    else
        cout << n << "번째 점은 없습니다." << endl;

    return 0;
}