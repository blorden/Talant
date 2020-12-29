;Программа для вычисления n-ого числа фибоначи

	in    
	pop rdx		;номер n-ого числа фибоначи


	push 0
	push 1

	pop  rbx	;в rbx будет рассматриваться текущее число (с номером 2 и более)
	pop  rax	;в rax - предыдущее

	push 1		;в rix будет лежать номер вычисленного фибаначи
	pop  rix

	call fib
	push rbx
	out

	hlt

fib:

	push rax    ;получаю следующую пару чисел из посл. фибоначи
	push rbx
	add
	pop  rbx
	pop  rax

	push rix	;получаю актуальный номер числа фибоначи в rbx
	push 1
	add
	pop  rix
	
	push rix	;проверяю, вычислил ли я нужное число фибоначи 
	push rdx
	cmp	

	jae	 return ;если да то вывожу его и завершаю программу

	call fib  	;иначе продолжаю его вычислять
	ret

return:

	ret