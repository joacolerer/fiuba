global  main
extern  puts
extern  printf
extern  gets
extern  sscanf
extern  fopen
extern  fread
extern  fclose

section .data
    vector      db  0 ,10 ,10 ,0  ,0   ,0
    
    col         dq  1

    CANT_COL    equ 6

    msj         db "Elemento sumado a acum: %hhi",10,13,0

    flujoMaximalTotal        db  0
section .bss

section .text
main:
    sub     rsp,8
loopVector:
    cmp     byte[col],5
    jg      termineFila
	
	mov		rax,[col]			;rax = columna
	dec		rax						;columna-1

	sub		rdx,rdx
	mov		dl,byte[vector+rax]

    mov     rdi,msj
    mov     rsi,rdx
    call    printf

    inc     byte[col]
    jmp     loopVector
termineFila:
    add     rsp,8

endProg:
ret
