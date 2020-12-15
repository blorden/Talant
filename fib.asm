	in
	pop  rdx    ;номер числа фибоначи

	push 0
	push 1

	pop  rbx
	pop  rax

	push 1		;в rix будет лежать номер вычисленного фибаначи
	pop  rix

	call fib
	push rbx
	out

	hlt

fib:
	
	push rax
	push rbx
	add
	pop  rbx
	pop  rax
	pop  rtx

	push rix
	push 1
	add

	pop  rix
	pop  rtx
	pop  rtx
	
	push rix 
	push rdx

	cmp	
	pop  rtx
	pop  rtx

	jae	 return

	call fib  
	ret

return:

	ret