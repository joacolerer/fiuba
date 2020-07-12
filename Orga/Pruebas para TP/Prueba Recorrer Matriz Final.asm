global  main
extern  puts
extern  printf
extern  gets
extern  sscanf
extern  fopen
extern  fread
extern  fclose

section .data

    msj         db "Elemento en pos %li el vector: %li",10,13,0

    verticesVisitados       dq  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   ;0 es no visitados o false, 1 es visitado o true
    padresVertices          dq  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 ;Aca se guarda el camino que se recorrio
    colaBFS                 dq  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
    longitudElemento        dq  8
section .bss
    contadorVerticesEnCola      resq 1
    punteroColaBFS              resq 1
    punteroAlmacenamientoCola   resq 1
section .text
main:
    sub     rsp,8
    ;call    inicializarVariablesBFS
    mov     rbx,1
loopVector:
    cmp     rbx,15
    jg      endProg
	
	mov		rax,rbx			;rax = columna
	dec		rax					;columna-1
    imul    rax,qword[longitudElemento]

	mov		rdx,qword[verticesVisitados+rax]

    mov     rdi,msj
    mov     rsi,rbx
    mov     rdx,rdx
    call    printf

    inc     rbx
    jmp     loopVector

    
endProg:
add     rsp,8
ret


inicializarVariablesBFS:

    mov     rdx,1
    mov     rcx, 16                             ; 15 nodos como maximo para el loop
loopInicVariablesBFS:
    mov     rdi,rdx
    dec     rdi
    imul    rdi,qword[longitudElemento]
    mov     qword[verticesVisitados + rdi], 0    ;Marco los visitados todos en false
    mov     qword[padresVertices + rdi], -1      ;Inicializo los padres en -1, de esta manera si no encuentra camino al deposito quedara en -1
    mov     qword[colaBFS + rdi],-1              ;Inicializo toda la cola con -1
    inc     rdx
    loop loopInicVariablesBFS
;Inicializo variables de la cola
    mov     qword[contadorVerticesEnCola],0
    mov     qword[punteroAlmacenamientoCola],0
    mov     qword[punteroColaBFS],0
ret