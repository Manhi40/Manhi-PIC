#include <p16f1789.inc>
    
    __CONFIG _CONFIG1, _FOSC_HS & _WDTE_OFF & _PWRTE_ON & _CP_OFF & _CPD_OFF & _BOREN_OFF
    
    cblock 0x20
    
    endc
    
    org 0
    
    
    
Config:
    movlw	0b10000000
    movwf	DAC1CON0
    
    
MainLoop:
    movlw	255
    movwf	DAC1CON1
    movlw	0
    movwf	DAC1CON1
    goto	MainLoop
    end