;Program Name:	Hex.exe
;Programmer:	Tim Beckett
;Date:		Septmeber 23,2002
;Language:		Visiual C++
;Flowchart:		See Flowchart
;Function:		This program will take a user enter decimal number and convert it into 
			a hexadecimal number
;Inputs:		decimal int
;Outputs:		hex value
;Other
;	Programs
;   	    Used:	N\A
;Data
;Restrictions:	N\A
;Method:		Get the chars
;			Convert to int
;			Calculate the Hex
;			Print the hex
;Printed
;	Output:	Enter a int: 123
;			The hex value is: 7b
;			Program completed. Hit any character to exit.


.486
.model flat, stdcall
.stack 1000h
include sasmacros.inc

.data

the_int dd 0
digit dd ?
x dd ?
t dd ?
x_place dd 16
char db ?
n db 0ah
m1 db 'Enter a int: ', 0
m2 db 'The hex value is: ',0

.code

main:
put_str m1
each_char:
	get_ch char
	compareb char, '9'
	bgz not_a_digit
	movezx digit, char
	isub digit, 48
	blz not_a_digit
	imult the_int, 10
	iadd the_int, digit
	br each_char

not_a_digit:
	move x, the_int
	put_str m2
convertion_loop:
	compare x, 15
	blez skip_convertion
 
calculation:
	move t, x
	idivi t, x_place
	compare t, 15
	bgz move_a_place
	imult x_place, t
	isub x, x_place
	compare t, 10
	bgez the_else
	iadd t, 48
	br print_out2

the_else:
	iadd t, 87

print_out2:
	put_ch t
	move x_place, 16
	br convertion_loop

move_a_place:
	imult x_place, 16
	br calculation

skip_convertion:
	compare x, 9
	bgz the_else2
	iadd x, 48
	br print_out1
  the_else2:
	iadd x, 87	
print_out1:
	put_ch x
	put_ch n
	done
end
	
