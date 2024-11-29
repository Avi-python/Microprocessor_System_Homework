?PR?_listen?listenINPUT	SEGMENT CODE 
	PUBLIC	_listen
	
	RSEG  ?PR?_listen?listenINPUT
_listen:
		MOV 	R7, #8
		SETB 	C
		MOV 	A, P2
LOOP:	RLC     A
		JNC		RETURN		
		DJNZ	R7, LOOP		
RETURN:	RET ; R7 is return value
END