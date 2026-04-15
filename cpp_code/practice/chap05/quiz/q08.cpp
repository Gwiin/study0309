#include <iostream>

using namespace std;

class Fitness{
private:
    /* data */
public:
    Fitness(/* args */);
    ~Fitness();
};

Fitness::Fitness(/* args */){

}

Fitness::~Fitness(){

}


int main(void){
    Fitness altong;
    altong.arrive("남", 3).ㅁㄱ걒ㄷ("여", 6).arrive("남", 9);
    
    int m = 0, w = 0;
    altong.count("남", m);
    altong.count("여", w);
    

    return 0;
}