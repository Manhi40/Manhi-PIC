; Universal PIC LCD Interface Module
; 74LS164-to-LCD test program
; By P. Pemberton, Jr.
; WWW: http://www.philpem.me.uk/
; Email: piclist@philpem.me.uk
; This software is distributed under the BSD License. You are free to do whatever
; you want with this code, but I would appreciate an email first. I would also
; appreciate copies of any modifications you make.
;
; Connections:
;	PIC	74LS164		LCD
;	RB7	1 and 2		via 10k resistor to "E"
;	RB6	8
;		5		D4
;		6		D5
;		10		D6
;		11		D7
;		12		RS
;		13			to 1N4148 cathode
;	Vcc	9 and 14	Vcc
;	Vss	7		Vss
;				E	to 1N4148 anode
;
;
; The contrast pin on the LCD should be connected as shown in the LCD module's
; datasheet.
;
; The above circuit is based on one included in an article written by
; Myke Predko for www.rentron.com

;; PIC setup and toplevel includes
	LIST	P=18f4550
	;INCLUDE	<p18f4550.inc>
	INCLUDE	"banks.inc"

; Pindefs
#DEFINE	LCD_DATA	PORTB,	7
#DEFINE	LCD_CLOCK	PORTB,	6

; Variables
	CBLOCK	0x20
	ENDC

; Reset vector
	ORG	0
	GOTO	START
; Interrupt vector
	ORG	4
	GOTO	START

; Start of code
	ORG	5

START:
	CLRF	PORTB			; Clear PORTB
	BANK1				; Bank 1
	BCF	LCD_DATA		; Data, clock=outputs
	BCF	LCD_CLOCK
	BANK0				; Bank 0

	CALL	LCD_INIT		; Init the LCD

	CLRF	FSR			; Message loop
MSGLOOP:
	MOVF	FSR,		W
	INCF	FSR,		F
	CALL	MESSAGE
	IORLW	.0
	BTFSC	STATUS,		Z
	GOTO	MSGDONE
	CALL	LCD_PUTCH
	GOTO	MSGLOOP

MSGDONE:
	MOVLW	.1			; Block Cursor on
	CALL	LCD_CURSBLINK
	CALL	LCD_LINE2
	MOVLW	"2"
	CALL	LCD_PUTCH
	MOVLW	"0"
	CALL	LCD_PUTCH
	MOVLW	"."
	CALL	LCD_PUTCH
	MOVLW	"0"
	CALL	LCD_PUTCH
	MOVLW	0x1A
	CALL	LCD_PUTCH
	GOTO	$

MESSAGE:
	ADDWF	PCL,		F
	DT	"Hello.",0

;; Final post-code includes
	INCLUDE	"lcd_ser.inc"

	END
