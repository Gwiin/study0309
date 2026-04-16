#include <iostream>

using namespace std;

class Fitness{
private:
    int male;
    int female;
    string gender;
public:
    Fitness();

    Fitness &arrive(string gen, int cnt);
    Fitness &at();

    void count(string gen, int &cnt);
};

Fitness::Fitness(){
    this->male = 0 ;
    this->female = 0 ;
}

Fitness &Fitness::arrive(string gen, int cnt){

}

Fitness &Fitness::at(){

}

void Fitness::count(string gen, int &cnt){

}


int main(void){
    Fitness altong;
    altong.arrive("남", 3).arrive("여", 6).arrive("남", 9);
    
    int m = 0, w = 0;
    altong.count("남", m);
    altong.count("여", w);
    

    return 0;
}