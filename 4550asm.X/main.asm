 #include <p18f4550.inc>
    
    
     CONFIG WDT = OFF
     CONFIG MCLRE = OFF
     CONFIG DEBUG = OFF
     CONFIG LVP = OFF
     CONFIG FOSC = INTOSCIO_EC
     
     cblock 0x20
Delay1
Delay2
Dig0
Dig1
Dig2
Dig1Code
Dig2Code
     endc
     
     org 0
     
Start:
    movlw	0x50
    movwf	OSCCON	    ; Set internal clock to 80 Mhz
    clrf	TRISD
    clrf	TRISB
    clrf	PORTD	 
    clrf	PORTB
    clrf	Dig0
    clrf	Dig1
    clrf	Dig2
    clrf	Dig1Code
    clrf	Dig2Code
    
MainLoop:
    
    movlw	0x01	    ; Select first digit
    movwf	LATB
    incf	Dig0	    ; Increments Dig0
    movlw	0x0A	    ; Moves literal 10 into WREG
    cpfseq	Dig0	    ; Compares Dig0 to 10, skip if equal
    goto	ItGood
    movlw	0x0
    movwf	Dig0
    ;goto	Tens
ItGood:
    movf	Dig0,0	    ; Move the value of Dig0 into WREG
    call	Inc7Seg	    ; Call Inc7Seg with the value of Dig0 in WREG
    movwf	LATD	    ; Moves the number onto the display
    movlw	0x02
    ;movwf	LATB
    ;movff	Dig1Code, LATD
   ; movlw	0x04
    ;movff	Dig2Code, LATD
    
    call	Delay
    goto	MainLoop    ; Loopback
    
Tens:
    movlw	0x02
    movwf	LATB
    incf	Dig0
Inc7Seg:
    mullw	0x02	    ; Multiply WREG by two 
    movf	PRODL,0	    ; Move the result into WREG
    addwf	PC	    ; Skip forward by that many instructions
    retlw	0x40	    ; 0
    retlw	0x79	    ; 1
    retlw	0x24	    ; 2
    retlw	0x30	    ; 3
    retlw	0x19	    ; 4
    retlw	0x12	    ; 5
    retlw	0x02	    ; 6
    retlw	0x78	    ; 7
    retlw	0x00	    ; 8
    retlw	0x10	    ; 9
    
Delay:
    movlw	0xFF
    movwf	Delay2
DelayLoop1:
    movlw	0xFF
    movwf	Delay1
DelayLoop2:
    decfsz	Delay1,f
    goto	DelayLoop2
    decfsz	Delay2,f
    goto	DelayLoop1
    return
    
end