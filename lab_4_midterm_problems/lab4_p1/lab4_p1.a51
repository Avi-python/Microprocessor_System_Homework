			; 411085025
			; Group 4
			org 0
			mov dptr, #Y_TABLE
			mov p1, #0ffH
RESTART:	mov a, p1
			cjne a, #0aH, CHECK
CHECK:		jc RETURN_Y
			mov p2, #0
			sjmp RESTART
RETURN_Y:	movc a, @a+dptr
			mov p2, a
			sjmp RESTART
			
			org 300H
Y_TABLE:	DB 5, 9, 15, 23, 33, 45, 59, 75, 93, 113
			end