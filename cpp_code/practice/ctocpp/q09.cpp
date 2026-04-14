#include <iostream>

using namespace std;

void swap(double *pa, double *pb);
void line_up(double *maxp, double *midp, double *minp);

int main(void){
 
    double max, mid, min;

    cout << "실수값 3개 입력 : " ;
    cin >> max >> mid >> min;
    line_up(&max, &mid, &min);
    cout << "정렬된 값 출력 : " << max << " " << mid << " " << min << endl;

    return 0;
}

void swap(double *pa, double *pb){
    double temp;

    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void line_up(double *maxp, double *midp, double *minp){
    while(1){
        if(*maxp > *midp && *midp > *minp)
            break;
        else if(*maxp < *midp)
            swap(maxp, midp);
        else if(*midp < *minp)
            swap(midp, minp);
    }

}
