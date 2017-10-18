#include <p12F683.inc>
     __config (_INTRC_OSC_NOCLKOUT & _WDT_OFF & _PWRTE_OFF & _MCLRE_OFF & _CP_OFF & _IESO_OFF & _FCMEN_OFF)
     cblock 0x20	    ; variables are defined here?
     endc

     org 0	            ; Start at flash address 0

Start:		    ; Essentially the void setup on arduino
     bsf	STATUS,RP0  ; Select Bank 1
     movlw	0x70	    ; Clock rate
     movwf	OSCCON	    ; set OSCCON to 0x70
     movlw	0b00010000
     movwf	TRISIO	    ; Set all pins as output, and GP1 as input
     clrf	ANSEL	    ; Set all ports as digital
     bcf	STATUS,RP0  ; Select Bank 0

MainLoop:
     btfsc	GPIO,4
     bsf	GPIO,2
     btfss	GPIO,4
     bcf	GPIO,2
     call	MainLoop
     
     end
     ; EOF: main.asm