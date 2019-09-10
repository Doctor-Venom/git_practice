#assemble using: as -gstabs --32 -o program1.o program1.s
#link using: ld -m elf_i386 -o program1 program1.o
#AT&T sytntax assembly x86 program for Linux OS that makes no sense

.data
	hellostr: .ascii "Hello World\n"
	otherstr: .asciz "Hello World"
	string: .ascii "return all life to the void from which it came"
	venom: .ascii "oooo innocence, break free, fly forth."
	integer: .int 2147483647
	short_int: .short 32767
	number: .byte 255
	arr: .int 10,20,30,40,50
	
.bss
	.comm buffer,10000
	.lcomm destination, 50
.text
.globl _start

_start:
	nop
	call function
	jmp continue
#making a syscall to print the hello string, syscall can be found in /usr/include/asm/unistd_32.h
	movl $4, %eax 
	movl $1, %ebx
	movl $hellostr, %ecx
	movl $12, %edx
	int $0x80
	#hello world printed

#move a value into registers	
	movl $1111111111, %eax
	movw $22222, %ax
	movb $33, %ah
	movb $00, %al

#move data between registers
	movl %eax, %ebx
	movw %bx, %cx
#move data between registers and memory
	movl integer, %eax
	movw %bx, short_int

#move a value into memory
	movl $0, integer
	movw $0, short_int
	movb $0, number
#moving data into indexed memory locations
	movl $0, %ecx
	movl $2, %edx
	movl $999, arr(%ecx,%edx,4)

	#movl $3, %edx
	#movl integer, arr(%ecx,%edx,4) #not valid for moving from memory to indexed memory

	#movl $0, %edx 
	#movl %eax, $arr(%ecx,%edx,4) #not valid for moving from registers into indexed memory
#indirect addressing using registers (like pointer stuff)
	movl $integer, %eax #put the address of the variable integer into register eax
	movl $123321, (%eax) #put the value 123321 into the address that is stored in the register eax
	movl $arr+1, %ebx
	movl $0, (%ebx)
	movl $0, -1(%ebx)
	movl $0, 1(%ebx)#why not working? the value of third element hasnt changed!
	movl $0, 2(%ebx)#why not working? the value of fouth element hasnt changed!

continue:
#usage of movsX instructions for strings
	movl $hellostr, %esi
	movl $destination, %edi
	movsb
	movsb
	movsw
	movsl
	movsl#destination will contain a string "Hello World\n"
	std #set direction flag (DF) so that esi and edi registers will be decremented when we se movsX, to reverse we will use cld
	movsl
	movsl
	movsl#contents wont change but the addresses in registers will change and go back to initial value
	cld

#usage of repitions (loops)
	movl $string, %esi
	movl $46, %ecx
	rep movsb

#loading strings from memory to registers
	movl $0, %eax
	leal string, %esi
	lodsb
	lodsb#this will replace the r with 'e'
	dec %esi
	dec %esi
	lodsw #the contents of eax will be "re"
	subl $2, %esi
	lodsl #will load "retu" to eax in big endian

#comparing strings
	leal hellostr, %esi
	leal otherstr, %edi
	cmpsl#compare 4 characters
	cmpsl
	cmpsl
	leal hellostr, %esi
	leal string, %edi
	cmpsl
#exit the program
	movl $1, %eax
	movl $0, %ebx
	int $0x80

function:
	movl $4, %eax
	movl $1, %ebx
	movl $string, %ecx
	movl $46, %edx
	int $0x80
	ret

print10:
	#we need to push and pop ecx value because we are using it in the loop, thats required to prevent infinite loop
	pushl %ecx
	movl $4, $eax
	movl $1, %ebx
	movl $hellostr, %ecx
	movl $12, %edx
	int $0x80
	pop %ecx
	loop print10

ven:38
	movl $4, %eax
	movl $1, %ebx
	movl $venom, %ecx
	movl $38, %edx
	int $0x80
