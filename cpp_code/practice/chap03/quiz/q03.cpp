#include <iostream>
#include <string>
using namespace std;

class Account{
private:
    string owner;
    int account;

public:
    void deposit(int money); //정수를 받아 계좌에 입금
    string getOwner(); //소유자 이름 리턴
    int withdraw(int money); // 계좌에서 정수만큼 출금
    int inquiry(); // 잔액 리턴

    Account(string name);
};


Account::Account(string name){
    owner = name;
    account = 0;
}

void Account::deposit(int money){   //정수를 받아 계좌에 입금
    account += money;
} 

string Account::getOwner(){     //소유자 이름 리턴
    return owner;
} 

int Account::withdraw(int money){      // 계좌에서 정수만큼 출금 //0이하로 출금할경우 최대출금 가능한 만큼만 출금

    if(account<money){
        money = account;
        account -= money; // account = 0;
    }
    else{
        account -= money;
    }
    return money;
} 

int Account::inquiry(){     // 잔액 리턴
    return account;
} 

//main===========================================================
int main(){
    Account a("황수희");
    a.deposit(20000);
    cout << a.getOwner() << " 잔액은 " << a.inquiry() << endl;
    int money = a.withdraw(15000);
    cout << money << "원 출금, ";
    cout << a.getOwner() << " 잔액은 "  << a.inquiry() << endl;
    money = a.withdraw(8000);
    cout << money << "원 출금, ";
    cout << a.getOwner() << " 잔액은 " << a.inquiry() << endl;

    return 0;
}