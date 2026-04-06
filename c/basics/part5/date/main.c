#include "date.h"

int main(void)
{
    Date d;

    setDate(&d, 2026, 03, 16);
    printDate(&d);
    return 0;

}