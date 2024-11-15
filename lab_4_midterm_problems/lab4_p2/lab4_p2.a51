			;411085025
			;Group 4
			org 0
MAIN:		acall TRANSFER
			acall CONVERT
			sjmp $

TRANSFER:	push 0
			push 0E0H
			push 82H
			push 83H
			mov dptr, #BCD_DATA
			mov r0, #80H
MOVE:		clr a
			movc a, @a+dptr
			mov @r0, a 
			cjne a, #0ffH, NEXT_LOC
			pop 83H
			pop 82H
			pop 0E0H
			pop 0
			ret	
NEXT_LOC:	inc r0
			inc dptr
			sjmp MOVE
			
CONVERT:	push 0
			push 1
			push 7
			push 0E0H
			mov r0, #80H
			mov r1, #40H
CONV:		mov a, @r0
			cjne a, #0ffH, KEEP_CONV 
			sjmp END_CONV
KEEP_CONV:	mov r7, a ; copy
			anl a, #0FH ; clear high nibble
			orl a, #30H
			mov @r1, a
			inc r1
			mov a, r7
			swap a
			anl a, #0fH
			orl a, #30H
			mov @r1, a
			inc r0
			inc r1
			sjmp CONV
END_CONV:	mov @r1, a
			pop 0E0H
			pop 7
			pop 1
			pop 0
			ret
			
			org 300H
BCD_DATA:	DB  76H, 87H, 01H, 92H, 34H, 55H, 0ffH
			end