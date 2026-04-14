#include <iostream>

using namespace std;

void input_nums(int *lotto_nums);
void print_nums(int *lotto_nums);

int main(void){
    int lotto_nums[6];

    input_nums(lotto_nums);
    print_nums(lotto_nums);

    return 0;
}

void input_nums(int *lotto_nums){ //배열에 로또 번호를 입력하는 함수
    //입력, 중복확인
    int num = 0;

    for(int i = 0; i < 6; i++){
        cout << "번호 입력 : ";
        cin >> num;
        lotto_nums[i] = num;
        for(int j = 0; j < i; j++){
            if(num == lotto_nums[j]){
                cout << "같은 번호가 있습니다!" << endl;
                i--;
                break;
            }
        }
    }
}


void print_nums(int *lotto_nums){ //배열에 저장된 값을 출력하는 함수
    //정렬
    int tmp = 0;
    for(int i = 0 ; i < 5 ; i++){
        for(int j = i + 1 ; j < 6 ; j++){
            if(lotto_nums[i] > lotto_nums[j]){
                tmp = lotto_nums[i];
                lotto_nums[i] = lotto_nums[j];
                lotto_nums[j] = tmp;
            }
        }
    }

    //출력
    for (int i = 0; i < 6 ; i++){
        cout << lotto_nums[i] << "  "; 
    }
    cout << endl;
}
