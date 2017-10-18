; Universal PIC LCD Interface Module
; HD44780 main handler/common functions (LCD_CMN.INC)
; NOTE: DO NOT #INCLUDE THIS FILE - #INCLUDE ONE OF THE BACKENDS INSTEAD!
; By P. Pemberton, Jr.
; WWW: http://www.philpem.me.uk/
; Email: piclist@philpem.me.uk
; This software is distributed under the BSD License. You are free to do whatever
; you want with this code, but I would appreciate an email first. I would also
; appreciate copies of any modifications you make.


	CBLOCK
		__LCD_DOCBUFF		; Display Control settings
	ENDC

; Initialize LCD
LCD_INIT:
	MOVLW	B'00000100'		; Init DOCBUFF
	MOVWF	__LCD_DOCBUFF
	CALL	__LCD_INIT		; Init the LCD
	RETURN				; Return

; Display Clear
LCD_CLRSCR:
	MOVLW	B'00000001'		; Clear the LCD display
	CALL	LCD_SENDINS
	RETURN

; Display On/Off - If W=0 then display off else display on
LCD_ONOFF:
	BSF	__LCD_DOCBUFF,	2	; Assume W != 0
	IORLW	0			; Update flags
	BTFSC	STATUS,		Z	; Zero?
	BCF	__LCD_DOCBUFF,	2	; W=0; turn off the display
	MOVF	__LCD_DOCBUFF,	W	; Move control byte into W
	IORLW	.8			; Set command bit
	CALL	LCD_SENDINS		; Send the instruction
	RETURN

; Cursor On/Off - If W=0 then cursor off else cursor on
LCD_CURSOR:
	BSF	__LCD_DOCBUFF,	1	; Assume W != 0
	IORLW	0			; Update flags
	BTFSC	STATUS,		Z	; Zero?
	BCF	__LCD_DOCBUFF,	1	; W=0; turn off the cursor
	MOVF	__LCD_DOCBUFF,	W	; Move control byte into W
	IORLW	.8			; Set command bit
	CALL	LCD_SENDINS		; Send the instruction
	RETURN

; Blinking Cursor On/Off - If W=0 then blinking cursor on else off
LCD_CURSBLINK:
	BSF	__LCD_DOCBUFF,	0	; Assume W != 0
	IORLW	0			; Update flags
	BTFSC	STATUS,		Z	; Zero?
	BCF	__LCD_DOCBUFF,	0	; W=0; turn off the block cursor
	MOVF	__LCD_DOCBUFF,	W	; Move control byte into W
	IORLW	.8			; Set command bit
	CALL	LCD_SENDINS		; Send the instruction
	RETURN

; Move cursor - W=offset
LCD_MOVECURS:
	IORLW	B'10000000'		; Set command bit
	CALL	LCD_SENDINS		; Send the instruction
	RETURN

; Move cursor to Line 1
LCD_LINE1:
	MOVLW	0x00			; Move cursor to 0x00
	CALL	LCD_MOVECURS
	RETURN

; Move cursor to Line 2
LCD_LINE2:
	MOVLW	0x40			; Move cursor to 0x40
	CALL	LCD_MOVECURS
	RETURN


