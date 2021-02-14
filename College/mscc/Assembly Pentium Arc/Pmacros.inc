; Pentium assembly code macros.
; Put the INCLUDE directive for this file before the .data and .code sections
; of source files that need the macros.

EXTERN putchar:NEAR
EXTERN getchar:NEAR
EXTERN puts:NEAR
EXTERN mainCRTStartup:NEAR
EXTERN _kbhit:NEAR

public main

 
done	MACRO
    LOCAL wait_on_input, exit_msg
    lea   EAX, exit_msg
	push  EAX
    call  puts
    add   ESP, 4   ;;  clean up stack from _printf call


wait_on_input:
     call  _kbhit
	 cmp   EAX, 0
	 je    wait_on_input

	 xor   EAX, EAX   ;; return without error
	 pop   edi
	 pop   esi
	 pop   ebx
	 leave
	 ret   0
exit_msg db 'Program completed. Hit any character to exit.',0
ENDM

at_my_code  MACRO
     xor  EAX, EAX ;; clears EAX
	 int  3
ENDM

put_ch   MACRO  thechar:REQ
     push	EAX
     push	EBX
     push	ECX
     push	EDX
     push	thechar
     call	putchar
	 add 	ESP, 4
	 pop	EDX
	 pop	ECX
	 pop	EBX
	 pop	EAX
ENDM

get_ch   MACRO
 	 push	EBX
     push	ECX
     push	EDX
     call   getchar ;; character in EAX
	 pop	EDX
	 pop	ECX
	 pop	EBX
ENDM

put_str  MACRO	stradr:REQ
     push	EAX
     push	EBX
     push	ECX
     push	EDX
     lea	EAX, stradr
     push	EAX
	 call	puts
	 add	ESP, 4
	 pop	EDX
	 pop	ECX
	 pop	EBX
	 pop	EAX
ENDM
