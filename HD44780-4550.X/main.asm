; Hitachi HD44780 driver for 4550
; Written by Eryk
; Uses PORTD for data bits
; PORTE 0,1 for r/s, E
#include <p18f4550.inc>

    
     CONFIG WDT = OFF
     CONFIG MCLRE = OFF
     CONFIG DEBUG = OFF
     CONFIG LVP = OFF
     CONFIG FOSC = INTOSCIO_EC
     
     cblock 0x20

     endc
     
     org 0
     
Start:
    movlw	0x70
    movwf	OSCON
    clrf	TRISD
    clrf	TRISE
    clrf	PORTD
    clrf	PORTE
    
Init:
    bcf		LATE, 0	    ; Set R/S to 0
    bcf		LATE, 1	    ; Set En to 0
    
    movlw	b'00111000' ; Function set, 8 bit, 2 lines, 5x7
    movwf	LATD
    
    bsf		LATE, 1	    ; Toggle En on and off
    bcf		LATE, 1
    
    movlw	b'00001111'
    movwf	LATD
    
    bsf		LATE, 1
    bcf		LATE, 1
    
DispWrite:
    