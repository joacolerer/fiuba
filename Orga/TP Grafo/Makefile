TpGrafo:	TpGrafo.o
		gcc -o TpGrafo.out TpGrafo.o -no-pie
TpGrafo.o: TpGrafo.asm
	nasm -f elf64 -g -F stabs TpGrafo.asm