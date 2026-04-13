#include <iostream>
using namespace std;


class Container{
private:
    int* p;
    int size;
public:
    void read();
    void write();
    void rotate();
    double avg();
    
    Container(int size);
    ~Container();
};

void Container::read(){
    cout << "정수 10개 입력>>";
    for (int i = 0 ; i < size ; i++){
        cin >> p[i];
    }
}

void Container::write(){
    for(int i = 0 ; i < size ; i++){
        cout << p[i] << " ";
    }
    cout << endl;
}

void Container::rotate(){
    int tmp = p[size-1];
    for(int i = 1 ; i <= size ; i++){
        p[size-i] = p[size-i-1];
    }
    p[0] = tmp;
}

double Container::avg(){
    double sum = 0.0;
    for(int i = 0 ; i < size ; i++){
        sum += p[i];
    }
    return sum/(double)size;
}

Container::Container(int size){
    this->p = new int[size];
    this->size = size;
}

Container::~Container(){
    delete p;
}



int main(void){
    Container c(10);
    c.read();
    c.write();
    c.rotate();
    c.write();
    cout << "평균은 " << c.avg() << endl;

    return 0;
}