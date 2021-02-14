;Program Name:	encryptor.exe
;Programmer:	Tim Beckett
;Date:			October 2, 2002
;Language:		Visiual C++
;Flowchart:		See Flowchart
;Function:		this program will take a user enter key of 5 letters
;				 and will encrypt a text message of up to 20 chars
;Inputs:		key, message
;Outputs:		encrypted message
;Other
;	Programs
;   	    Used:	NA
;Data
;Restrictions:	NA
;Method:		get key
;			get message
;			sum like this k->m e->e y->s k->s e->a y->g k->e
;			then get the mod of each sum
;			print encrypted message
;Printed
;	Output:	Enter a key 4 chars long:great
;			Enter the message up to 20 chars:helloworld
;			nvplhcfvlw
;			Program completed. Hit any character to exit.

.486
.model flat, stdcall
.stack 1000h
include sasmacros.inc

.data

key dd 5 dup(0)
key_pntr dd ?
msg dd 20 dup(0)
msg_pntr dd ?
letter db ?
msg1 db 'Enter a key 4 chars long:', 0
msg2 db 'Enter the message up to 20 chars:', 0
new_line db 0ah
counter dd 0
msg_cnt dd 0
key_num dd ?
msg_num dd ?
end_key dd ?

.code
main:
	la key_pntr, key
	put_str msg1
key_loop:
	get_ch letter
	compare counter, 4
	bgz stop_key
	iadd counter, 1
	isub letter, 97
	movezx m(key_pntr), letter
	iadd key_pntr, 4
	br key_loop
stop_key:
	la msg_pntr, msg
	put_str msg2
msg_loop:
	get_ch letter
	compareb letter, 'a'
	blz stop_msg
	isub letter, 97
	compare msg_cnt, 20
	bez stop_msg
	iadd msg_cnt, 1
	movezx m(msg_pntr), letter
	iadd msg_pntr, 4
	br msg_loop
stop_msg:
	la key_pntr, key
	move end_key, key_pntr
	iadd end_key, 16
	la msg_pntr, msg
	move counter, 0
print_encryption:
	compare counter, msg_cnt
	bez stop_print
	move key_num, m(key_pntr)
	move msg_num, m(msg_pntr)
	iadd msg_num, key_num
	irem msg_num, 26
	iadd msg_num, 97
	put_ch msg_num
	iadd counter, 1
	iadd msg_pntr, 4
	compare key_pntr, end_key
	bez key_reset
	iadd key_pntr, 4
	br print_encryption
key_reset:
	isub key_pntr, 16
	br print_encryption
stop_print:
	put_ch new_line
	done
end
