		; 411085025
		org 0
		mov r2, #0
		mov r7, #0
		mov a, #0
LOOP:	add a, #1
		jnc NEXT
		inc r7
NEXT:	djnz r2, LOOP
		mov r6, a
		nop ; only for screenshot
		end