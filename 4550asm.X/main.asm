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
Dig0Code
Dig1Code
Dig2Code
     endc
     
     org 0
     
Start:
    movlw	0x70
    movwf	OSCCON	    ; Set internal clock to 80 Mhz
    
    movlw	b'11001111' ; Timer0 config
    movwf	T0CON	    ; Move Timer0 config into T0CON
    
    clrf	TRISD
    clrf	TRISB
    clrf	PORTD	 
    clrf	PORTB
    clrf	Dig0
    clrf	Dig1
    clrf	Dig2
    clrf	Dig0Code
    clrf	Dig1Code
    clrf	Dig2Code
    
MainLoop:
    movlw	0xF0
    cpfslt	TMR0L
    call	IncDisp
    
    movlw	0x01	    ; Select first digit
    setf	LATD
    movwf	LATB
    movff	Dig0Code, LATD
    nop
    nop
    movlw	0x02
    setf	LATD
    movwf	LATB
    movff	Dig1Code, LATD
    nop
    nop
    movlw	0x04
    setf	LATD
    movwf	LATB
    movff	Dig2Code, LATD
    nop
    nop
    setf	LATD
    goto	MainLoop
    
IncDisp:
    incf	Dig0	    ; Increments Dig0
    movlw	0x0A	    ; Moves literal 10 into WREG
    cpfseq	Dig0	    ; Compares Dig0 to 10, skip if equal
    goto	ItGood
    movlw	0x0
    movwf	Dig0
ItGood:
    movf	Dig0,0	    ; Move the value of Dig0 into WREG
    call	Inc7Seg	    ; Call Inc7Seg with the value of Dig0 in WREG
    movwf	Dig0Code    ; Moves the number onto the display
    
    return
    
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
    
    
end