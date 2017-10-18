
#DEFINE LCD_D7 PORTA,5
#DEFINE LCD_D6 PORTA,4
#DEFINE LCD_D5 PORTA,3
#DEFINE LCD_D4 PORTA,2
#DEFINE LCD_EN PORTA,1
#DEFINE LCD_RS PORTA,0
	
	cblock
    
	endc
	org 0x8
LCD_INIT:
    MOVF    0b01001000	    ; Set 4bit
    MOVWF   PORTA
    
    MOVF    0b01001000	    ; Function set, 8 bit
    MOVWF   PORTA	    ; Nibble 1
    MOVF    0b01100000
    MOVWF   PORTA	    ; Nibble 2
    
    CLRF    PORTA	    ; Entrymode, nibble 1
    BSF	    PORTA,1
    MOVF    0b01110000
    MOVWF   PORTA	    ; Nibble 2
    
    MOVF    0b11010000
    MOVWF   PORTA
    MOVF    0b11100000
    MOVWF   PORTA
    
    CLRF    PORTA
    return
    
    
    