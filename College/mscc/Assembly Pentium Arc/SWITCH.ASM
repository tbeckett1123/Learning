; pentium coded program to print out the a inversed string
;Program Name:	switch.exe
;Programmer:	Tim Beckett
;Date:			10-24-02
;Language:		Visiual C++
;Flowchart:		See Flowchart
;Function:		This program will take a user entered string and will invert
;					the letters of the string and then print the new letters, but it
;					will not change numbers. They	will be printed as is.
;Inputs:			string of chars, each char will be put in EAX
;Outputs:		string of inverted chars
;Other
;	Programs
;   	 Used:	N/A
;Data
;Restrictions:	if al >= 48(ASCII VALUE) && al <= 57(ASCII VALUE) then skip the
;					convertion and print the char
;					after xor al by 32, if al <= 42 end program
;Method:			loop:	get a char
;							if al >= 48(ASCII VALUE) && al <= 57(ASCII VALUE) then skip
;							the convertion and print the char
;							xor the char by 32(base 10)
;							if char <= 42(base 10) then end program
;							if cnt < 1 {print "New string is "; cnt+=1}
;							print char
;							goto loop
;Printed
;	Output:


.486
.model flat, stdcall
.stack 1000h
include Pmacros.inc
title switch program

.data

msg1 db 'Enter string: ', 0
msg2 db 'New string is ', 0
cnt dd 0
endL db 0ah

.code

	 main:	put_str msg1
				get_ch
get_loop:	cmp al, 48
				jge check
 convert:	xor al, 32
				cmp al, 42
				jle stop_get
				cmp cnt, 1
				jge prnt
				put_str msg2
				add cnt, 1
	 prnt:	put_ch eax
				get_ch
				jmp get_loop
	check:	cmp al, 57
				jle prnt
				jmp convert
stop_get:	put_str endL
				done
end
