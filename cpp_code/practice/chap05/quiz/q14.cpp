#include <iostream>
#include <string>
using namespace std;

class Contest
{
private:
    string *teams;
    int *scores;
    int size;
public:
    Contest(int size);
    Contest(const Contest &src);
    ~Contest();

    void read();
    int getSize() { return size; }
    int getScore(int index) { return scores[index]; }
    string getTeam(int index) { return teams[index]; }
};

Contest::Contest(int size){
    this->size = size;
    this->teams = new string [size];
    this->scores = new int [size];
    for (int i = 0 ; i < size ; i++){
        this->teams[i] = "0";
        this->scores[i] = 0;
    }
}

Contest::Contest(const Contest &src){
    this->size = src.size;
    this->teams = new string [this->size];
    this->scores = new int [this->size];
    for (int i = 0 ; i < this->size ; i++){
        this->teams[i] = src.teams[i];
        this->scores[i] = src.scores[i];
    }
}

Contest::~Contest(){
    if(this->teams){
        // cout << "팀 할당 해제" << endl;
        delete [] this->teams;
    }
    if(this->scores){
        // cout << "스코어 할당 해제" << endl;
        delete [] this->scores;
    }
}

void Contest::read(){
    cout << this->size << "개 입력>>";
    for(int i = 0 ; i < this->size ; i++){
        cin >> this->teams[i] >> this->scores[i]; 
    }
}

string decideGoldAward(Contest codingTest);


int main(){
    Contest codingTest(6);
    codingTest.read();
    string team = decideGoldAward(codingTest);

    // for(int i = 0 ; i < codingTest.getSize() ; i++){
    //     cout << codingTest.getTeam(i) << " " << codingTest.getScore(i) << endl;
    // }
    cout << "금상은 " << team << "팀입니다." << endl;
    
    return 0;
}

string decideGoldAward(Contest codingTest){
    string gold;
    int index = 0;

    for(int i = 0 ; i < (codingTest.getSize()-1) ; i++){
        if(codingTest.getScore(index) < codingTest.getScore(i+1)){
            index = i+1;
        }
    }
    gold = codingTest.getTeam(index);
    return gold;
}