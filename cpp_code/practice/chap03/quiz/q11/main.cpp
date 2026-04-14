#include <iostream>
#include "Oval.h"
using namespace std;

int main(void){
    Oval kitae, jane(10,15);
    kitae.set(3,4);
    kitae.show();
    cout << jane.getWidth() << "x" << jane.getHeight() << ", 면적 " << jane.area() << endl;

    return 0;
}