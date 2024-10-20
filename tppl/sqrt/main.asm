;	������� (�������) ��� ��������� ����
; �������� �������� ��������� � ����
%macro pushd 0
	push rax
	push rbx
	push rcx
	push rdx
%endmacro

;������� �� �����
%macro popd 0
	pop rdx
        pop rcx
        pop rbx
        pop rax
%endmacro

;������� � �������
%macro print 2
	mov rax, 1 ;������� ������
        mov rdi, 1 ;�����
        mov rsi, %1 ;���������� ��� ������
        mov rdx, %2 ;�� ����� � ������
        syscall ;��������� � ������ �����������
        
%endmacro

; ����� ������� ����� ��� ������ (� asm ��� �������� �����)
%macro dprint 0
	pushd
	mov rbx, 0
	mov rcx, 10
	%%divide:
	        xor rdx, rdx
	        div rcx
	        push rdx
	        inc rbx
	        cmp rax, 0
	        jne %%divide

	%%digit:
        	pop rax
        	add rax, '0'
		mov [result], rax
		print result, 1
		dec rbx
		cmp rbx, 0
		jg %%digit

	mov rsi, newline
	mov rdx, nlen
	print rsi, rdx

	popd
%endmacro

section .data
	number dd 324

	newline db 0xA, 0xD
	nlen equ $ - newline


section .text
global _start

_start:
	xor rcx, rcx

	mov eax, [number]
	shr eax, 1
	mov ebx, eax 	;x1 = num / 2

	mov eax, [number]
    	xor edx, edx
    	idiv ebx
    	add eax, ebx
    	shr eax, 1	;x2 = (x1 + (num / x1)) // 2
    	
    	sub ebx, eax
	cmp edx, 1

.sqrt:
	inc rcx
	
	mov ebx, eax	;x1 = x2
	
	mov eax, [number]
    	xor edx, edx
    	idiv ebx
    	add eax, ebx
    	shr eax, 1	;x2 = (x1 + (num / x1)) // 2
    	
	sub ebx, eax
	
	dprint
	
	cmp rcx, 10
	jg .fin

	cmp edx, 1
	jge .sqrt
	
.fin:

	dprint
	mov rax, 60
	xor rdi, rdi
	syscall


section .bss
	result resb 1

