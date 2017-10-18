          LIST
; PIC16-series PAGE-switching macros
; By P. Pemberton, Jr.
; WWW: http://www.philpem.me.uk/
; Email: piclist@philpem.me.uk
; This software is distributed under the BSD License. You are free to do whatever
; you want with this code, but I would appreciate an email first. I would also
; appreciate copies of any modifications you make.
;
; Provides:
;       BANK0           Switch to RAM BANK 0
;       BANK1           Switch to RAM BANK 1
;       BANK2           Switch to RAM BANK 2
;       BANK3           Switch to RAM BANK 3
          NOLIST

#ifndef   __BANKS_INCLUDED
 #define  __BANKS_INCLUDED

BANK0     MACRO                         ; Macro to select data RAM BANK 0
          BCF       STATUS,RP0
          BCF       STATUS,RP1
          ENDM

BANK1     MACRO                         ; Macro to select data RAM BANK 1
          BSF       STATUS,RP0
          BCF       STATUS,RP1
          ENDM

BANK2     MACRO                         ; Macro to select data RAM BANK 2
          BCF       STATUS,RP0
          BSF       STATUS,RP1
          ENDM

BANK3     MACRO                         ; Macro to select data RAM BANK 3
          BSF       STATUS,RP0
          BSF       STATUS,RP1
          ENDM
#endif
          LIST