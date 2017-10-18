; Universal PIC LCD Interface Module
; HD44780 4-bit mode transport layer/backend (LCD_4BIT.INC)
; By P. Pemberton, Jr.
; WWW: http://www.philpem.me.uk/
; Email: piclist@philpem.me.uk
; This software is distributed under the BSD License. You are free to do whatever
; you want with this code, but I would appreciate an email first. I would also
; appreciate copies of any modifications you make.
;
; Pindefs required:
; 	LCD_D7	The PIC pin connected to the LCD's D7 pin (ex: PORTB,3)
;	LCD_D6	The PIC pin connected to the LCD's D6 pin (ex: PORTB,2)
;	LCD_D5	The PIC pin connected to the LCD's D5 pin (ex: PORTB,1)
;	LCD_D4	The PIC pin connected to the LCD's D4 pin (ex: PORTB,0)
;	LCD_E	The PIC pin connected to the LCD's E pin (ex: PORTB,5)
;	LCD_RS	The PIC pin connected to the LCD's RS pin (ex: PORTB,4)

#DEFINE LCD_D7 PORTA,5
#DEFINE LCD_D6 PORTA,4
#DEFINE LCD_D5 PORTA,3
#DEFINE LCD_D4 PORTA,2
#DEFINE LCD_E  PORTA,1
#DEFINE LCD_RS PORTA,0
	
        CBLOCK
                __LCD_TEMP0
                __LCD_TEMP1
        ENDC

; Send a byte to the LCD, assumes RS already set
__LCD_SEND:
	MOVWF	__LCD_TEMP0		; Store byte in Temp 0
	BCF	LCD_D7			; Clear data bits
	BCF	LCD_D6
	BCF	LCD_D5
	BCF	LCD_D4
	BTFSC	__LCD_TEMP0,	7	; Load high nibble
	BSF	LCD_D7
	BTFSC	__LCD_TEMP0,	6
	BSF	LCD_D6
	BTFSC	__LCD_TEMP0,	5
	BSF	LCD_D5
	BTFSC	__LCD_TEMP0,	4
	BSF	LCD_D4
	BSF	LCD_E			; Strobe E
	GOTO	$+1
	BCF	LCD_E

	BCF	LCD_D7			; Clear data bits
	BCF	LCD_D6
	BCF	LCD_D5
	BCF	LCD_D4
	BTFSC	__LCD_TEMP0,	3	; Load low nibble
	BSF	LCD_D7
	BTFSC	__LCD_TEMP0,	2
	BSF	LCD_D6
	BTFSC	__LCD_TEMP0,	1
	BSF	LCD_D5
	BTFSC	__LCD_TEMP0,	0
	BSF	LCD_D4
	BSF	LCD_E			; Strobe E
	GOTO	$+1
	BCF	LCD_E
	RETURN

; Send an instruction byte to the LCD
LCD_SENDINS:
	BCF	LCD_RS			; RS low=instruction
	CALL	__LCD_SEND		; Send the instruction byte
	CALL	__LCD_SHORTDELAY	; Short delay for instruction
	RETURN

; Send a character to the LCD
LCD_PUTCH:
	BSF	LCD_RS			; RS high=character
	CALL	__LCD_SEND		; Send the character
	CALL	__LCD_SHORTDELAY	; Short delay for data
	RETURN

; Initialize the LCD
__LCD_INIT:
	CALL	__LCD_LONGDELAY		; Long init delay
	MOVLW	B'00110011'		; 2x 8bit resets
	CALL	LCD_SENDINS
	MOVLW	B'00110011'		; 2x 8bit resets
	CALL	LCD_SENDINS
	MOVLW	B'00110010'		; 8bit reset then 4bit reset
	CALL	LCD_SENDINS
	MOVLW	B'00101100'		; Function Set - 4bit, 2 lines
	CALL	LCD_SENDINS
	MOVLW	B'00000110'		; Mode Set - incr. w/crsr shift
	CALL	LCD_SENDINS
	MOVLW	B'00001100'		; Display on, cursor & blink off
	CALL	LCD_SENDINS
	MOVLW	B'00000001'		; Display Clear
	CALL	LCD_SENDINS
	MOVLW	B'00000010'		; Cursor Home
	CALL	LCD_SENDINS
	CALL	__LCD_LONGDELAY		; Long post-init delay
	RETURN

; Long delay for init
__LCD_LONGDELAY:
	CLRF	__LCD_TEMP0
__LCD_LONGDEL:
	CLRF	__LCD_TEMP1
__LCD_SHORTDEL:
	DECFSZ	__LCD_TEMP1,	F
	GOTO	__LCD_SHORTDEL
	DECFSZ	__LCD_TEMP0,	F
	GOTO	__LCD_LONGDEL
	RETURN

; Short delay between commands
__LCD_SHORTDELAY:
	MOVLW	0x14
	MOVWF	__LCD_TEMP1
__LCD_SHORTLOOP:
	DECFSZ	__LCD_TEMP1,	F
	GOTO	__LCD_SHORTLOOP
	RETURN

; Include the Common LCD Functions
	INCLUDE	"lcd_cmn.inc"


