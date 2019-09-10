;this program is written assembly x86 intel syntax for Linux OS that gets input (numbers) and converts it to integer then print it
;assemble using nasm -f elf32 -g -F dwarf asm_program1.s
;link using ld -m elf_i386 -o asm_program1 asm_program1.o

section .data

section .bss
	temp resb 6

section .text
global _start
_start:
	nop
	call get_input
	call convert
	call print
	jmp valid_exit

get_input:
	mov eax, 3
	mov ebx, 0
	mov ecx, temp
	mov edx, 6
	int 0x80
	mov byte [temp+eax-1], 0	;to replace the \n at the end of the input (in case input length is less than 6)
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
		jb invalid_exit
		cmp edx, '9'
		ja invalid_exit
		sub edx, '0'
		add eax, eax			;this 2 lines i found on SO are a way to perform eax*=10
		lea eax, [eax + eax * 4]	;without modifing edx register (AHUET!)
		add eax, edx
		jmp .loop1
	.done:
	ret

print:
	mov ecx, 0
	.loop1:
		mov ebx, 10
		mov edx, 0
		div ebx			;quotient in EAX and reminer in EDX
		add edx, '0'
		push edx
		inc ecx
		cmp eax, 0
		jnz .loop1
	.loop2:
		mov esi, ecx
		mov eax, 4
		mov ebx, 1
		mov ecx, esp
		mov edx, 1
		int 0x80
		mov ecx, esi
		add esp, 4
		loop .loop2
	


valid_exit:
	mov eax, 1
	mov ebx, 0
	int 0x80

invalid_exit:
	mov eax,1
	mov ebx, 999
	int 0x80
