#include <iostream>
using namespace std;

//함수 중복 선언
// bool equals(string x, string y);
// bool equals(string x, string y, int n);
// bool equals(string x, string y, int n, string z);


//디폴트 매개변수 함수 선언
bool equals(string x, string y, int n=0, string z = "");

int main(void){
    string x = "Prof. Hwang";
    string y = "Prof. KiM";
    string z = "Prof. Lee";
    if(equals(x,y)) cout << "같음" << endl;
    if(equals(x,y,3)) cout << "앞 3글자 같음" << endl;
    if(equals(x,y,5,z)) cout << "앞 5글자 같음" << endl;

    return 0;
}

//디폴트매개변수 함수 구현
bool equals(string x, string y, int n, string z){
    if(n==0){
        if(x == y) return true;
        else return false;
    }
    else if(z==""){
        if( x.substr(0,n) == y.substr(0,n) ) return true;
        else return false;
    }
    else{
        if( (x.substr(0,n) == y.substr(0,n)) && (y.substr(0,n) == z.substr(0,n))) return true;
        else return false;
    }
}

//함수 중복 구현
// bool equals(string x, string y){
//     if( x == y ){
//         return true;
//     }
//     return false;
// }

// bool equals(string x, string y, int n){
//     if ( x.substr(0,n) == y.substr(0,n) ){
//         return true;
//     }
//     return false;
// }

// bool equals(string x, string y, int n, string z){
//     if( (x.substr(0,n) == y.substr(0,n)) && (y.substr(0,n) == z.substr(0,n))){
//         return true;
//     }
//     return false;
// }



