			; 411085025
			; Group 4
			org 0
MAIN:		acall P1_STATUS
			acall LOOKUP
			sjmp MAIN

P1_STATUS:	push 7
			mov p1, #0ffH
			mov r7, #8 ; should start at high bit, because low bit will be don't care which will lead to unexpected result.
			mov a, p1
CHECK:		rlc a
			jnc	FIND_ZERO
			djnz r7, CHECK
FIND_ZERO:	mov a, r7
			pop 7 ; a is LOOKUP's arg, so I don't store it in stack 
			ret
			
LOOKUP: 	cpl a ; can use complement to calculate.	
			mov p2, a
			ret
			end