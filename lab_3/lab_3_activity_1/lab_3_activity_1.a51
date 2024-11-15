		; 411085025
		; Group 4
		org 0
		mov r0, #40H
		mov r2, #4
		mov dptr, #TABLE
AGAIN:	mov a, @r0
		movc a, @a+dptr
		mov p1, a
		acall DELAY
		inc r0
		djnz r2, AGAIN
		sjmp $
		
		; Expect: 921600 MC, Actual: 921618
DELAY:  mov r7, #5
LOOP_3: mov r6, #240
LOOP_2: mov r5, #255
LOOP_1: nop
		djnz r5, LOOP_1
		djnz r6, LOOP_2
		djnz r7, LOOP_3
		ret
		
		org 300H
TABLE:	DB '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
		end