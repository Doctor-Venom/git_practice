;assembly x86 program written in intel syntax for Linux OS
;takes numeric inputs until 0 or until 1000000 numbers are entered, then calculates the MIN, MAX, and the sum of entered numbers and prints them
;in case of overflow of SUM, a message is printed eaxh time it is overflowed

;assemble using nasm -f elf32 -g -F dwarf asm_program1.s
;link using ld -m elf_i386 -o asm_program1 asm_program1.o

section .data
        str1 db "enter positive numbers to fill the array, enter 0 to stop:", 13, 10
        len1 equ $-str1
        str2 db 13,10,"maximum element:",13, 10
        len2 equ $-str2
        str3 db 13,10,"minimum element:", 13, 10
        len3 equ $-str3
        str4 db 13,10,"sum of numbers:", 13, 10
        len4 equ $-str4
	str5 db 13,10,"DONE",13,10
	len5 equ $-str5
	str6 db 13,10,"[-]SUM OVERFLOW, add 4294967296 to the printed sum",13,10
	len6 equ $-str6
	stopval dd "0"

section .bss
        temp resb 9
        arr resd 1000008
        min resd 1
        max resd 1
        sum resd 1

%macro write_str 2
	push eax
	push ebx
	push ecx
	push edx
	mov eax, 4
	mov ebx, 1
	mov ecx, %1
	mov edx, %2
	int 0x80
	pop edx
	pop ecx
	pop ebx
	pop eax
%endmacro

section .text
global _start

print:
        mov ecx, 0
	mov ebx, 10
        .label1:
        mov edx, 0	;required to pevent floating point exception in some cases
        div ebx         ;quotient in EAX and reminder in EDX (we need the reminder)
        add edx, '0'
        push edx
        inc ecx
        cmp eax, 0
        jnz .label1

        .label2:
        mov esi, ecx
        mov eax, 4
        mov ebx, 1
        mov ecx, esp
        mov edx, 1
        int 0x80
        mov ecx, esi
	add esp, 4
        loop .label2
        ret

convert:
	mov ebx, 10
	xor eax, eax
	mov esi, 0
	;mov ecx, temp
	.loop1:
		movzx edx, byte [temp+esi]
		inc esi
		test edx, edx
		jz .done
		cmp edx, '0'
		jb error
		cmp edx, '9'
		ja error
		sub edx, '0'
		add eax, eax			;this 2 lines are a way to perform eax*=10
		lea eax, [eax + eax * 4]	;without modifing edx register
		add eax, edx
		jmp .loop1
	.done:
	ret

_start:
        nop
	write_str str1, len1

        mov ebx, 0			;offset value for arr
        mov ecx, 1000000		;max number of input values

        input_loop:
	mov dword [temp], 0		;clear the variable
        push ecx			;save the state of ecx
	push ebx			;save ebx state
        mov eax, 3
        mov ebx, 0
        mov ecx, temp
        mov edx, 10
        int 0x80			;sys_read call
	mov byte [temp+eax-1], 0	;remove \n at the end of input in case its len was < 9
	mov esi, temp
	mov edi, stopval
	cmpsd				;if input value == 0 then break and go to compare stage
        jz compare
	mov ecx, eax			;put the number of entered bytes as a counter for convert loop
	call convert			;after converting eax will contain the value in decimal
	pop ebx				;restore ebx state
	mov edi, arr			;destination address into edi
	add edi, ebx
	stosd				;store eax into memory in the array
        add ebx, 4			;increment array offset
        pop ecx				;restore the state of ecx
        loop input_loop

	compare:
	mov eax, -1			;number of counted values in arr
	mov edx, arr			;move the base address of arr into edx
	sub edx, 4
	count_loop:
	inc eax
	add edx, 4
	cmp dword [edx], 0		;compare value in arr with 0
	jnz count_loop			;if comparison result = false then loop again
	mov ecx, eax			;set the quotient as a counter for compare_loop
	mov esi, 0			;this will be the offset in arr
	mov eax, [arr]			;initialize min with the first item in the arr
	mov ebx, eax			;initialize max with the first item in arr
	mov edx, 0			;initialize sum with 0
	compare_loop:			;in this loop eax=min / ebx=max / edx=sum
	push ecx			;save counter state
	mov ecx, [arr+esi]		;load avalue from memory into ecx
	cmp ebx, ecx			;compare with min
	jle .next1			;jump if ecx less or equal
	mov ebx, ecx			
	.next1:
	cmp eax, ecx			;compare with max
	jge .next2			;jump if ecx greater or equal
	mov eax, ecx			
	.next2:
	add edx, ecx			;add the value to the sum
	jno .next3			;jump if no overflow in eax
	write_str str6, len6
	.next3:
	add esi, 4			;increment the offset by 4 (dword)
	pop ecx				;restore counter state
	loop compare_loop

	mov dword [max], eax		;store max in memory
	mov dword [min], ebx		;store min in memory
	mov dword [sum], edx		;store sum in memory

	write_str str2, len2		;print str2
	mov eax, [max]			;move max into eax
	call print			;print max
	write_str str3, len3		;pint str3
	mov eax, [min]			;move min to eax
	call print			;print min
	write_str str4, len4		;print str4
	mov eax, [sum]			;move sum to eax
	call print			;print sum

exit:
	write_str str5, len5
	mov eax, 1
	mov ebx, 0
	int 0x80

error:
	mov eax, 1
	mov ebx, -1
	int 0x80
