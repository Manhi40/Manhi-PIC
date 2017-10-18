/* 
 * File:   MyFunctions.h
 * Author: Eryk Zagorski
 *
 * Created on May 10, 2017, 9:35 PM
 */

#ifndef MYFUNCTIONS_H
#define	MYFUNCTIONS_H
#include <p18f4550.h>
#include <adc.h>

void delay(int ms);
void readJoy(int *x, int *y);
void writeMatrix(int row, int col);

#endif	/* MYFUNCTIONS_H */

