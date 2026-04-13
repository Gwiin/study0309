#include <iostream>
using namespace std;


int main(){

    int arysize = 0;
    cout << "구입할 물품의 개수>>";
    cin >> arysize;

    int *price  = new int(arysize);

    cout << "물품 " << arysize << "개의 가격 입력>>";
    for(int i = 0; i<arysize ; i++){
        cin >> *(price+i);
    }

    int max = price[0];
    int min = price[0];

    for (int i = 1 ; i < arysize ; i++){
        if(max < price[i]){
            max = price[i];
        }
        if(min > price[i]){
            min = price[i];
        }
    }

    cout << "제일 싼 가격은 " << min << endl;
    cout << "제일 비싼 가격은 " << max << endl;
    
    delete price;
    return 0;
}