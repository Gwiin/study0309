#pragma once
#include <stdio.h>


typedef struct
{
    int year;
    int month;
    int day;
}Date;


void printDate(Date *pDate);
void setDate(Date *pDate, int year, int month, int day);
