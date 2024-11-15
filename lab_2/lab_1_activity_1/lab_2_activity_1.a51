		; 411085025
		org 0
		mov a, #0
		mov r7, #0
		add a, #92H
		jnc NEXT_1
		inc r7
NEXT_1:	add a, #23H
		jnc NEXT_2
		inc r7
NEXT_2: add a, #66H
		jnc NEXT_3
		inc r7
NEXT_3: add a, #87H
		jnc NEXT_4
		inc r7
NEXT_4: add a, #0F5H
		jnc NEXT_5
		inc r7
NEXT_5: mov r6, a
		nop ; just for screenshot
		end
		