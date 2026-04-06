#include "date.h"


void printDate(Date *pDate)
{
    printf("%d-%d-%d\n", pDate->year, pDate->month, pDate->day);
}




void setDate(Date *pDate, int year, int month, int day)
{
    pDate->year = year;
    pDate->month = month;
    pDate->day = day;
}

