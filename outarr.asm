;Программа для нахождения суммы на отрезке

	in
	pop  rnx					;кол-во чисел в исходном массиве

	push 0
	pop  rix
	call read					;читаю исходный масив

	push 0
	pop rix 
	call write					;вывожу исходный масив

	hlt


read:							;чтение массива

	push rix
	push rnx
	cmp

	jae  return

	in
	pop  [rix]

	call inc
	call read

	ret

return:							;возврат функции

	ret


inc:							;функция увеличения rix на один

	push rix
	push 1
	add
	pop  rix

	ret


write:							;вывод массива

	push rix
	push rnx
	cmp

	jae  return

	push [rix]
	out

	call inc
	call write

	ret