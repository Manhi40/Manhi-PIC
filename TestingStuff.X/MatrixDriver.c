/*
 * File:   MatrixDriver.c
 * Author: Eryk Zagorski
 *
 * Created on May 8, 2017, 10:19 PM
 */

#include <p18cxxx.h>
#include <math.h>

void LedMatrix(int row, int col) {
    
    if(row > 3 || col >7){
        return;
    }
    
    TRISC = 0;
    TRISB = 0;
    
    PORTB = pow(2, col);
    PORTC = pow(2, row);
    
    return;
}
