#include <p18f4550.inc>
#include "lcd.inc"
    CONFIG WDT = OFF
    CONFIG MCLRE = ON
    CONFIG DEBUG = OFF
    CONFIG LVP = OFF
    CONFIG FOSC = INTOSCIO_EC
    
    cblock 0x20
    timed
    endc
    
    org 0

Start:
    call    LCD_INIT
Dead:
    goto    Dead
    END
    