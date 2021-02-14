.486
.model flat, stdcall
.stack 1000h
include sasmacros.inc

.data

	sum1 dd 1
	sum2 dd ?
	n dd 1
	good db 'Good Job!', 0ah, 0
	try db 'Try Again!', 0ah, 0
	newl db 0ah, 0
	suma db 'Sum1', 0ah, 0
	sumb db 'Sum2', 0ah, 0

.code

main:
	while:
		compare n, 99
		bgz stop_while
		iadd n, 1
		move sum2, n
		imult sum2, sum2
		iadd sum1, sum2
		br while
	stop_while:
	imult sum1, sum1
	move sum2, n
	iadd sum2, 1
	imult sum2, n
	imult n, 2
	iadd n, 1
	imult sum2, n
	idivi sum2, 6
	compare sum1, sum2
	bnz else
	put_str good
	br endif
	else:
	put_str try
	endif:
	put_str suma
	put_i sum1
	put_str sumb
	put_i sum2
	done
end