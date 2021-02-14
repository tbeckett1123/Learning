;Program Name:	remove1.exe
;Programmer:	Tim Beckett
;Date:			12-06-02
;Language:		Visiual C++
;Flowchart:		See Flowchart
;Function:		This program will take in a string and remove the
;				duplicated chars
;Inputs:		a string
;Outputs:		the shortened string
;Other
;	Programs
;   	 Used:	n/a
;Data
;Restrictions:	*eax must contain an address to a string when you
;				 call print_s
;				*the chars must be great than 20h and less than 127h
;				 on the ASCII chart
;				*the first item on the stack must be a pointer to a
;				 string, and the second item on the stack must be
;				 the length of that string, when you call check
;Method:		get the string
;				replace the dup chars w/ 6h
;				push the remaining chars on the stack
;				pop the chars of the stack into a string pointer
;				reverse the chars because they are backwards
;				print the string
;Printed
;	Output:		SEE PRINTED OUTPUT

.486
.model flat, stdcall
.stack 1000h
include Pmacros.inc
title switch program

.data
len dd 0
chars db 'YYOOU OUUHOAAYVYVE HHITTE',0
msg db 'Enter a string',0

.code
main:		lea ebx, chars
			put_str msg
			get_ch
get_loop:	cmp al, 20h
			jl stop_get
			cmp al, 7fh
			jge stop_get
			mov byte ptr[ebx], al
			inc len
			inc ebx
			get_ch
			jmp get_loop
stop_get:	mov byte ptr[ebx], 0
			lea eax, chars
			mov  ebx, len
			push eax
			push ebx
			call check
			lea eax, chars
			call print_s
			done

check:		push ebp
			mov ebp, esp
			sub esp, 16
			mov eax, dword ptr[ebp+12]
			mov ecx, 0
f_loop1:	cmp ecx, dword ptr[ebp +8]
			jge get_out1
			push ecx		
			mov ecx, 0		
			mov ebx, eax	
			inc ebx
f_loop2:	cmp ecx, dword ptr[ebp +8]	
			jg get_out2
			mov dl, byte ptr[ebx]	
			cmp dl, 20h	
			je skip
			cmp dl, 0h
			je skip
			cmp dl, byte ptr[eax]
			jne	skip
			mov dl, 6h
			mov byte ptr[ebx], dl			
skip:		inc ebx			
			inc ecx			
			jmp f_loop2		
get_out2:	inc eax
			pop ecx
			inc ecx
			jmp f_loop1
get_out1:	mov eax, dword ptr[ebp+12]
			call print_s
			add esp, 16
			mov ebx, 0
			mov ecx, 0
			mov edx, 0
			mov eax, dword ptr[ebp+12]
f_loop3:	cmp ebx, dword ptr[ebp+8]
			jge get_out3
			cmp byte ptr [eax], 6h
			je skip1
			push [eax]
			inc edx
skip1:		inc eax
			inc ebx
			jmp f_loop3
get_out3:	inc edx
			push 0h
			mov ebx, 0
			mov eax, dword ptr[ebp+12]
f_loop4:	cmp ebx, edx
			jge get_out4
			pop [eax]			
			inc eax
			inc ebx
			jmp f_loop4
get_out4:	mov ebx, 0
			mov eax, dword ptr[ebp+12]
f_loop7:	cmp ebx, edx
			jge get_out7
			push [eax]			
			inc eax
			inc ebx
			jmp f_loop7
get_out7:	mov ebx, 0
			mov eax, dword ptr[ebp+12]
f_loop6:	cmp ebx, edx
			jge get_out6
			pop [eax]
			inc eax
			inc ebx
			jmp f_loop6
get_out6:	mov esp, ebp
			pop ebp
			ret

print_s:	cmp byte ptr[eax], 0
			je get_out5
			put_ch [eax]
			inc eax
			jmp print_s
get_out5:	put_ch 0ah
			ret 
end
