#include <iostream>
#include <string>
using namespace std;

class Memo{
private:
    string date;
    string content;


public:

    void show();
    bool isSameDate(Memo b);
    string getDate();
    string getContent();

    Memo(string date, string content);
};


void Memo::show(){
    cout << this->date << ", " << this->content << endl;
}

bool Memo::isSameDate(Memo b){
    if(this->date == b.date){
        return true;
    }
    else
        return false;
}

string Memo::getDate(){
    return this->date;
}

string Memo::getContent(){
    return this->content;
}



Memo::Memo(string date, string content){
    this->date = date;
    this->content = content;
}



int main(void){
    Memo a("1:20" , "동계 프로그래밍 캠프");
    Memo b("2:20" , "김경미 독일 송별회");
    Memo c("2:21" , "박채원 졸업식. 대학원 간대");

    a.show();
    if(a.isSameDate(b)) cout << "같은 날입니다." << endl;
    else cout << "다른 날입니다." << endl;
    cout << b.getDate() << "에 " << b.getContent() << endl;
}