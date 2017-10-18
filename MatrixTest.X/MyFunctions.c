/*
 * File:   MyFunctions.c
 * Author: Eryk Zagorski
 *
 * Created on May 10, 2017, 9:36 PM
 */


#include "MyFunctions.h"

void delay(int ms){
    int i, j;
    
    for(i=0;i<ms;i++){
        for(j=0;j<2;j++){
        }
    }
}

void readJoy(int* x, int* y){
    ADCON0bits.CHS0 = 0;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE != 0);
    *y = ADRESH;

    ADCON0bits.CHS0 = 1;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE != 0);
    *x = ADRESH;
}

void writeMatrix(int row, int col){
    int c;
    LATB = pow(2, col);
    c = pow(2, row);
    LATD = (255 ^ c);
}