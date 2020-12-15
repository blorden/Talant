;Программа для решения квадратного уравнения
;ax^2 + bx + c = 0	

	in
	in
	in

	pop  rcx 			;c
	pop  rbx			;b
	pop  rax			;a

	push rax
	push 0
	cmp

	je   lin_ur	    	;т.к. a = 0, сводится к линейному уравнению
	jne  sq_eq	   		

lin_ur:

	push rbx
	push 0
	cmp

	je   simple     	;т.к. a = 0 и b = 0, сводится к проверке равенства

	push 1				;вывожу кол-во решений
	out

	push 0				;вывожу решение линейного уравнения
	push rcx
	sub
	push rbx
	div
	out

	hlt

simple:					;проверка равенства свободного члена с нулем

	push rcx			;сравниваю свободный член и ноль
	push 0
	cmp

	je   infinity_roots ;если они не равны
	jne  no_roots		;если они равны

no_roots:				;если решений нет

	push -10000000		
	out

	hlt

infinity_roots:			;если решений бесконечно много

	push 10000000
	out

	hlt

one_root:				;если решение одно

	push 1
	out

	push 0
	push rbx
	sub
	push 2
	div
	push rax
	div
	out

	hlt

two_roots:				;если решений несколько
	
	push 2				;вывожу кол-во решений
	out

	push 0				;вывожу первое решение
	push rbx			
	sub
	push rdx
	sub
	push 2
	div
	push rax
	div
	out

	push 0				;вывожу второе решение
	push rbx			
	sub
	push rdx
	add
	push 2
	div
	push rax
	div
	out

	hlt

sq_eq:					;решение квадратного уравнения при ненулевом старшем коэф.

	push rbx			;rdx = b^2
	push rbx
	mul
	pop  rdx

	push rax			;rdx = b^2 - 4ac
	push 4
	mul
	push rcx
	mul
	pop  rtx
	push rdx
	push rtx
	sub
	pop  rdx

	push rdx			;если дискриминант меньше нуля
	push 0
	cmp
	jb   no_roots  

	push rdx			;rdx = sqrt(b^2 - 4ac)
	sqrt
	pop  rdx

	push rdx			;проверяю, был ли дисриминант равен нулю
	push 0
	cmp

	je   one_root		;если дискриминант равен нулю
	jne  two_roots	    ;если дисриминант больше нуля