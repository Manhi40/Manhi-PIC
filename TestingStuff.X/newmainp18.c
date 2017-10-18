/*
 * File:   newmainp18.c
 * Author: Eryk Zagorski
 *
 * Created on May 8, 2017, 7:02 PM
 */

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

#include <p18F4550.h>
#include <delays.h>
#include <usart.h>

// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = INTOSCIO_EC// Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#include <math.h>
#include <adc.h>

void delay(int ms);
void readJoy(int *x, int *y);
void pwmWrite(int c);


void main(void) {
    unsigned int joyY, joyX;
    int i, j;
    TRISB = 0;
    
    ADCON0 = 0b00000000;
    ADCON1 = 0b00000100;
    ADCON2 = 0b00001000;
    ADCON0bits.ADON = 0X01;
    
    TRISC &=0xFD;
    
    CCP1CON &= 0xCF;
    CCP1CON |= 0x0C;
    
    PR2 = 0b01111100;
    T2CON = 0x03;
    
    CCPR1L = 0b00011111;
    CCP1CON = 0b00011100;
    
    
    while(1){
        
        /*pwmWrite(0);
        delay(1000);
        pwmWrite(50);
        delay(1000);
        pwmWrite(100);
        delay(1000);
        */
        readJoy(&joyX, &joyY);
        
        if(joyY > 150 && joyY > joyX){
            LATB = 0b00000001;
        }
        else if(joyY < 100 && joyY < joyX){
            LATB = 0b00000010;
        }
        else if(joyX > 150 && joyX > joyY){
            LATB = 0b00000100;
        }
        else if(joyX < 100 && joyX < joyY){
            LATB = 0b00001000;
        }
        else if(joyX > 101 && joyX < 149 && joyY > 101 && joyY < 149){
            LATB = 0;
        }
        
    }
    
    return;
}

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

void pwmWrite(int c){
    
    CCPR1L = c>>2;
    CCP1CON &= 0xCF;
    CCP1CON |= ((c<<4)&0x30);
}