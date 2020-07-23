global  main
extern  puts
extern  printf
extern  gets
extern  sscanf

section .data
;Matriz de adyacencia del grafo
    grafo       dq  0,0,10,10,0
                dq  0,0,0,20,8
                dq  0,30,0,0,0
                dq  0,0,5,0,0
                dq  0,0,0,0,0
;Mensajes de entrada
    msgBienvenida           db 10,"Materia: Organizacion del computador.",10,"Trabajo practico numero 20: Flujo maximal de un grafo.",0
    msgExplicacionTP        db "El algoritmo a ser usado es el algoritmo de Ford-Fulkerson para enocntrar el flujo maximal de un grafo implementado en Assembly",0
    msgAutor                db "Realizado por Joquin Matias Lerer",10,  "Padron numero: 105.493",10, "Fecha: 1 Cuatrimestre (virtual) 2020",10,0
    msgSeparador            db "------------------------------------Comienzo de programa------------------------------------",10,0
;Mensajes de validacion de vertices
    msgIngresoCantVertices  db "Ingrese la cantidad de vertices del grafo (Numero entero entre 5 y 15)",0
    msgErrorFormatoVertice  db "Ingrese un formato numerico valido",0
    msgErrorCantVertices    db "Ingrese un numero de vertices entre 5 y 15",0
    formatoVertice          db "%li",0
    longitudElemento        dq  8
;Mensaje de salida
    msgMostrarFlujoMax      db "El flujo maximal del grafo es: %li",10,0
    msgMostrarCamino        db "El subcamino recorrido es:[",0
    msgMostrarVerticeCamino db "%li,",0
    msgMostrarUltimoVerticeCamino db "%li]",0
    msgFlujoMinimo          db " y el flujo minimo del camino es: %li",10,0

;Variables de BFS (maximo de 15 nodos)
    verticesVisitados       dq  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   ;0 es no visitados o false, 1 es visitado o true
    padresVertices          dq  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 ;Aca se guarda el camino que se recorrio
    colaBFS                 dq  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1

    fila                    dq 0
    col                     dq 0

section .bss
    plusRsp		                resq    1
    ingresoTeclado              resq    1
;BFS
    cantidadVerticesGrafo       resq    1
    contadorVerticesEnCola      resq    1
    punteroColaBFS              resq    1
    punteroAlmacenamientoCola   resq    1
    verticeActual               resq    1
    contadorForBFS              resq    1
;FordFulkerson
    flujoMaximo                 resq    1
    flujoMinimoDeCamino         resq    1
    verticeActualFordFulkerson  resq    1
    padreActual                 resq    1
;Mostrar camino
    contadorMostrarRecorrido    resq    1
    vectorCaminoArmado          times 15 resq 1
    indiceMostrarCamino         resq    1
   
section .text
main:
    sub     rsp,8
;Muestro mensajes de bienvenida
    mov     rdi,msgBienvenida
    call    puts

    mov     rdi,msgExplicacionTP
    call    puts

    mov     rdi,msgAutor
    call    puts

    mov     rdi,msgSeparador
    call    puts

;Pido Ingreso de la cantidad de vertices
validarVertices:
    mov     rdi,msgIngresoCantVertices
    call    puts

ingresoVertice:
    mov     rdi,ingresoTeclado
    call    gets

    mov     rdi,ingresoTeclado
    mov     rsi,formatoVertice
    mov     rdx,cantidadVerticesGrafo
    call    sscanfLinux
;Valido el formato
    cmp     rax,1
    jl      errorFormatoVertices
;Valido el rango logica (5 a 15)
    cmp     qword[cantidadVerticesGrafo],5
    jl      errorVerticesFueraDeRango

    cmp     qword[cantidadVerticesGrafo],15
    jg      errorVerticesFueraDeRango
;Llamo a la funcion/subrutina fordFulkerson
    call    fordFulkerson
;Muestro el flujo maximo calculado
    mov     rdi,msgMostrarFlujoMax
    mov     rsi,qword[flujoMaximo]
    call    printfLinux

endProg:
    add     rsp,8
ret


;Funciones auxiliares
errorFormatoVertices:
    mov     rdi,msgErrorFormatoVertice
    call    puts
    jmp     ingresoVertice
ret

errorVerticesFueraDeRango:
    mov     rdi, msgErrorCantVertices
    call    puts
    jmp     ingresoVertice
ret



;Algoritmo principal de Ford-Flukerson. En donde se calcula el flujo minimo de un camino y actauliza aristas y aristas inversas del grafo.

fordFulkerson:
    mov     qword[flujoMaximo],0

;Estructura de while de Ford-Fulkerson
whileFordFulkerson:

;Mientras haya camino desde el nodo fuente al nodo deposito calculo el flujo que se puede mandar por ese camino
    call    bfs

;Me fijo si el nodo deposito fue visitado al volver de bfs, si no fue visitado termino y vuelvo al main para mostrar el flujo final
    mov     rax,qword[cantidadVerticesGrafo]
    dec     rax
    imul    rax,qword[longitudElemento]                                   

    cmp     qword[verticesVisitados + rax],0
    je      endFordFulkerson

    mov     qword[flujoMinimoDeCamino],100000000            ;Inicio el primer valor de flujo de cada camino un numero exageradamente alto asi siempre el primer peso cuenta como minimo

;Encuentro el flujo minimo del camino encontrado
    call    encontrarFlujoMinimoDeCamino

;Actualizo el grafo
    call    actualizarGrafo

;Agrego el flujo del camino al flujo total
    mov     rax,qword[flujoMaximo]
    add     rax,qword[flujoMinimoDeCamino]
    mov     qword[flujoMaximo],rax

;Armo el recorrido para mostrarlo por pantalla
    call    armarRecorrido
    jmp     whileFordFulkerson

endFordFulkerson:
ret

;Subrutina para encontrar el flujo minimo de un camino
encontrarFlujoMinimoDeCamino:
    mov     rax,qword[cantidadVerticesGrafo]
    dec     rax
    mov     qword[verticeActualFordFulkerson],rax           

inicioForFLujoMinimoDeCamino:
    cmp     qword[verticeActualFordFulkerson],0             ;Si llegue a la fuente dejo de recorrer
    je      finEncontrarFlujoMinimoDeCamino

    call    conseguirPadre                                  ;Consigo padre del vertice actual

;Me desplazo en la matriz para buscar el peso entre el vertice actual y su padre
    mov     rax,qword[padreActual]
    imul    rax,qword[longitudElemento]
    imul    rax,qword[cantidadVerticesGrafo]

    mov     rbx,rax

    mov     rax,qword[verticeActualFordFulkerson]
    imul    rax,qword[longitudElemento]

    add     rbx,rax                                         ;rbx contiene el desplazamiento de la matriz

    mov     rdx,qword[grafo + rbx]                          ;Guardo en rdx el peso de la arista
    

    cmp     rdx,qword[flujoMinimoDeCamino]                  ;Lo comparo con el flujo minimo que tenga en el momento 
    jg      continuarLoop                                   ;Si el flujo es mayor continuo el loop

    mov     qword[flujoMinimoDeCamino],rdx                  ;Si llegue aca significa que el peso de la arista es menor que el flujoMinimo y entonces actualizamos este flujoMinimo

    call    continuarLoop
    jmp     inicioForFLujoMinimoDeCamino
finEncontrarFlujoMinimoDeCamino:
ret

;Subrutina para actualizar las aristas y las aristas inversas del grafo
actualizarGrafo:
    mov     rax,qword[cantidadVerticesGrafo]
    dec     rax
    mov     qword[verticeActualFordFulkerson],rax

;Aca se usan dos variables, verticeActualFordFulkerson siempre contiene el vertice actual que se esta evaluando y padreActual su padre
loopActualizarGrafo:
    cmp     qword[verticeActualFordFulkerson],0             ;Si llegue a la fuente dejo de recorrer
    je      finActualizarGrafo

    call    conseguirPadre                                  ;Consigo padre del vertice actual

;Resto la capacidad a las aristas de los vertices del camino recorrido
    mov     rcx,qword[longitudElemento]
    lea     rsi,[padreActual]
    lea     rdi,[fila]
    rep     movsb

    mov     rcx,qword[longitudElemento]
    lea     rsi,[verticeActualFordFulkerson]
    lea     rdi,[col]
    rep     movsb

    call    calcularDesplazamientoGrafo                     ;Desplazamiento almacenado en rbx

    mov     rax,qword[grafo + rbx]
    sub     rax,qword[flujoMinimoDeCamino]
    mov     qword[grafo + rbx], rax

;Aumento la capacidad de las aristas inversas de los vertices del camino recorrido
    mov     rcx,qword[longitudElemento]
    lea     rsi,[verticeActualFordFulkerson]
    lea     rdi,[fila]
    rep     movsb

    mov     rcx,qword[longitudElemento]
    lea     rsi,[padreActual]
    lea     rdi,[col]
    rep     movsb

    call    calcularDesplazamientoGrafo                     ;Desplazamiento almacenado en rbx

    mov     rax,qword[grafo + rbx]
    add     rax,qword[flujoMinimoDeCamino]
    mov     qword[grafo + rbx], rax

    call    continuarLoop
    jmp     loopActualizarGrafo

finActualizarGrafo:
ret

;Cuando continuo el loop tengo que conseguir el padre del verticeActual y pasarlo al verticeActual
continuarLoop:
    call    conseguirPadre
    mov     rcx,qword[longitudElemento]
    lea     rsi,[padreActual]
    lea     rdi,[verticeActualFordFulkerson]
    rep     movsb
ret
;Conseguir padre consigue el padre del verticeActual y lo almacena en padreActual
conseguirPadre:
    mov     rsi,qword[verticeActualFordFulkerson]
    imul    rsi,qword[longitudElemento]
    mov     rdi,qword[padresVertices + rsi]
    mov     qword[padreActual],rdi
ret


;Subrutina para armar el recorrido  y mostrarlo
armarRecorrido:
;Para mostrar el recorrido armo un vector con los padres de cada vertice del camino y lo guardo en orden, despues para
;mostrarlo correctamente lo recorro al reves. Para hacer estonecesito saber cuantos elementos hay

    mov     qword[contadorMostrarRecorrido],0

    mov     rax,qword[cantidadVerticesGrafo]
    dec     rax
    mov     qword[vectorCaminoArmado + 0],rax       ;guardo como primer valor el vertice deposito
    inc     qword[contadorMostrarRecorrido]

;Muestro la primer parte del mensaje
    mov     rdi,msgMostrarCamino
    call    printfLinux

;Asignacion vertice actual con la cantidad de vertices para buscar el padre del deposito apenas entramos al loop
    mov     qword[verticeActualFordFulkerson],rax
loopArmarRecorrido:

    call    conseguirPadre

    mov     rax,qword[contadorMostrarRecorrido]
    imul    rax,qword[longitudElemento]

;Guardo el padre en el vector de camino
    mov     rcx,qword[longitudElemento]
    lea     rsi,[padreActual]
    lea     rdi,[vectorCaminoArmado + rax]
    rep     movsb
    inc     qword[contadorMostrarRecorrido]

;Reemplazo el vertice actual con el padre actual asi sigo buscando el camino
    mov     rcx,qword[longitudElemento]
    lea     rsi,[padreActual]
    lea     rdi,[verticeActualFordFulkerson]
    rep     movsb

;Cuando llego al vertice fuente termine de armar el recorrido
    cmp     qword[verticeActualFordFulkerson],0
    je      mostrarCaminoEnPantalla

;Si no mostro el recorrido es que no llego a la fentefuente y hay que seguir buscando padre
    jmp     loopArmarRecorrido

endArmarRecorrido:
ret

;Muestro el vector de camino al reves, asi se muestra correctamente.
mostrarCaminoEnPantalla:
    mov     rbx,qword[cantidadVerticesGrafo]
    dec     rbx

    dec     qword[contadorMostrarRecorrido]
loopMostrarCaminoEnPantalla:
    mov     rax,qword[contadorMostrarRecorrido]
    imul    rax,qword[longitudElemento]

;Pregunto por el ultimo elemento asi lo muestro con otro formato y no queda una "," de mas al final
    cmp     qword[vectorCaminoArmado + rax],rbx
    je      mostrarUltimoElemento

    mov     rdi,msgMostrarVerticeCamino
    mov     rsi,qword[vectorCaminoArmado + rax]
    call    printfLinux
ultimoElemento:
    dec     qword[contadorMostrarRecorrido]
;Si el contador es negativo es que ya no tengo mas elementos para mostrar y termino
    cmp     qword[contadorMostrarRecorrido],0
    jl      endMostrarCaminoEnPantalla
    jmp     loopMostrarCaminoEnPantalla
endMostrarCaminoEnPantalla:
ret

mostrarUltimoElemento:
    mov     rdi,msgMostrarUltimoVerticeCamino
    mov     rsi,qword[vectorCaminoArmado + rax]
    call    printfLinux

    mov     rdi,msgFlujoMinimo
    mov     rsi,qword[flujoMinimoDeCamino]
    call    printfLinux
    jmp     ultimoElemento
ret

;Realiza un recorrido bfs sobre el grafo, el cual va a llenar un vector [padresVertices] con el camino posible que encontro desde la fuente hasta el 
;deposito. Este mismo fue inicializado en -1 para indicar que no hay camino (seria False). Cualquier camino, para que sea valido
;tendra que visitar si o si el ultimo vertice, es decir el deposito. Si no lo visito, significa que no se encontro un camino.

bfs:
;Inicializacions pre while de BFS
    call    inicializarVariablesBFS

    call    encolarFuente

;Marco la fuente como visitado
    mov     qword[verticesVisitados + 0],1

whileBFS:

;Condicion de while, si no hay nada en la cola termino el bfs
    cmp     qword[contadorVerticesEnCola],0
    je      finBFS

;Desencolar guarda el elemento desencola en la variable verticeActual
    call    desencolar

    mov     qword[contadorForBFS],0
loopBFS:

;Si el contador llego al deposito termino el for
    mov     rsi,qword[contadorForBFS]       
    cmp     qword[cantidadVerticesGrafo],rsi
    je      whileBFS

    imul    rsi,qword[longitudElemento]
    
;Pregunto si el vertice ya fue visitado, si fue visitado buscamos siguiente vertice
    cmp     qword[verticesVisitados+rsi],1      
    je      siguienteVerticeLoop

;Calculo el desplazamiento para obtener el peso de la arista entre el vertice desencolado y el contador del for
    mov     rcx,qword[longitudElemento]
    lea     rsi,[verticeActual]
    lea     rdi,[fila]
    rep     movsb

    mov     rcx,qword[longitudElemento]
    lea     rsi,[contadorForBFS]
    lea     rdi,[col]
    rep     movsb   

    call    calcularDesplazamientoGrafo     

    mov     rax,qword[grafo+rbx]                ;rbx contiene el desplazamiento total de la matriz de adyacencia

;Si no tiene peso significa que no hay arista entre esos vertices y buscamos siguiente vertice 
    cmp     rax,0                               
    je      siguienteVerticeLoop

;Si llegamos aca significa que el verticeActaul no fue visitado y tiene peso > 0
    call    encolarVertice                      
    call    asignarPadre
    call    marcarVisitado

    inc     qword[contadorForBFS]
    jmp     loopBFS

finBFS:
ret

siguienteVerticeLoop:
    inc     qword[contadorForBFS]
    jmp     loopBFS
ret

;Subrutina para inicializar los vectores y las variables que usa la cola
inicializarVariablesBFS:

    mov     rbx,1
loopInicVariablesBFS:

    cmp     rbx,15
    jg      termineLoopVariables
    
    mov     rdi,rbx
    dec     rdi
    imul    rdi,qword[longitudElemento]

    mov     qword[verticesVisitados + rdi], 0   ;Marco los visitados todos en false
    mov     qword[padresVertices + rdi], -1     
    mov     qword[colaBFS + rdi],-1             

    inc     rbx
    jmp     loopInicVariablesBFS

termineLoopVariables:

;Inicializo variables de la cola
    mov     qword[contadorVerticesEnCola],0
    mov     qword[punteroAlmacenamientoCola],0
    mov     qword[punteroColaBFS],0

ret

encolarFuente:
    mov     qword[colaBFS],0                    
    inc     qword[contadorVerticesEnCola]   

;Despues de encolar, actualizo el puntero de almacenamiento asi puedo encolar el proximo en la posicion correcta    
    add     qword[punteroAlmacenamientoCola],8  
ret


desencolar:
    mov     rsi,qword[punteroColaBFS]           ;Uso el puntero a la cola como indice
    mov     rbx,qword[colaBFS+rsi]           
    mov     qword[verticeActual], rbx           ;Lo guardo como vertice actual

    add     qword[punteroColaBFS],8             ;Actualizo punteros de cola para seguir encolando correctamente
    dec     qword[contadorVerticesEnCola]       
ret

calcularDesplazamientoGrafo:
    mov     rax,qword[fila]
    imul    rax,qword[longitudElemento]
    imul    rax,qword[cantidadVerticesGrafo]

    mov     rbx,rax
    
    mov     rax,qword[col]
    imul    rax,qword[longitudElemento]

    add     rbx,rax
ret

;Encolo el contador del for
encolarVertice:
    mov     rdi,qword[contadorForBFS]
    mov     rsi,qword[punteroAlmacenamientoCola]
    mov     qword[colaBFS+rsi],rdi

    inc     qword[contadorVerticesEnCola]
    add     qword[punteroAlmacenamientoCola],8
;Actualizo el puntero de almacenamiento para encolar correctamente
ret

;Guardo en la posicion del vertice actual, su padre
asignarPadre:
    mov     rbx,qword[contadorForBFS]
    imul    rbx,qword[longitudElemento]
    mov     rsi,[verticeActual]
    mov     qword[padresVertices + rbx],rsi
ret

marcarVisitado:
    mov     rdi,qword[contadorForBFS]
    imul    rdi,qword[longitudElemento]
    mov     qword[verticesVisitados + rdi],1
ret


;FUNCIONES EXTRA BASADAS EN UN TEMPLATE DEL FORO DE ORGANIZACION DEL COMPUTADOR PARA HACER SSCANF Y PRINTF DE MANERA CORRECTA EN LINUX, HECHA POR UN ALUMNO

sscanfLinux:
    call	    checkAlign
    sub		    rsp,[plusRsp]
    call	    sscanf
    add		    rsp,[plusRsp]
    ret

printfLinux:
    push        rax
    mov         rax,0
    call        printf
    pop         rax
ret

    ; ----------------------------------------
    ; ----------------------------------------
    ; ****	checkAlign ****
    ; ----------------------------------------
    ; ----------------------------------------
checkAlign:
    push        rax
    push        rbx
    push        rdx
    push        rdi

    mov         qword[plusRsp],0
    mov		    rdx,0

    mov		    rax,rsp
    add         rax,8 ; para sumar lo q restó la CALL
    add		    rax,32   ; para sumar lo que restaron las PUSH

    mov		    rbx,16
    idiv	    rbx      ; rdx:rax / 16   resto queda en RDX

    cmp         rdx,0 ; Resto = 0?
    je		    finCheckAlign
    mov         qword[plusRsp],8
finCheckAlign:
    pop         rdi
    pop         rdx
    pop         rbx
    pop         rax
ret