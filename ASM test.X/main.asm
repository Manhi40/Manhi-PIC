#include <p12F683.inc>
     __config (_INTRC_OSC_NOCLKOUT & _WDT_OFF & _PWRTE_OFF & _MCLRE_OFF & _CP_OFF & _IESO_OFF & _FCMEN_OFF)
     cblock 0x20
Delay1                    ; Define two 8-bit variables for the
Delay2                    ; delay loop: Delay1 and Delay2
     endc

     org 0                ; Start at flash address 0
Start:
     bsf    STATUS,RP0    ; Select Registers at Bank 1
     movlw  0x70
     movwf  OSCCON        ; Set the internal clock speed to 8 Mhz
     clrf   TRISIO        ; Set all General Purpose I/O to output
     clrf   ANSEL         ; Make all ports as digital I/O
     bcf    STATUS,RP0    ; Back to Registers at Bank 0    

MainLoop:
     bsf    GPIO,2        ; Set GP2 Output To High
     call   Delay         ; Call Delay Subroutine
     bcf    GPIO,2        ; Clear GP2 Output To Low
     call   Delay         ; Call Delay Subroutine
     nop                  ; No Operation
     goto   MainLoop      ; Goto MainLoop
Delay:
     movlw  0xFF
     movwf  Delay2
DelayLoop1:
     movlw  0xFF
     movwf  Delay1
DelayLoop2:
     decfsz Delay1,f      ; Decrease Delay1, If zero skip the next instruction
     goto   DelayLoop2    ; Not zero goto DelayLoop2
     decfsz Delay2,f      ; Decrease Delay2, If zero skip the next instruction
     goto   DelayLoop1    ; Not zero goto DelayLoop1
     return               ; Return to the Caller
     end
; EOF: HelloWorld.asm