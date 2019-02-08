assignment01 : main.o fti.o dti.o itf.o ftd.o dtf.o
	gcc -lm -o assignment01 main.o fti.o dti.o itf.o ftd.o dtf.o

main.o : main.c fti.c dti.c itf.c ftd.c dtf.c
	gcc -c main.c

fti.o :
	gcc -c fti.c

dti.o :
	gcc -c dti.c

itf.o :
	gcc -c itf.c

ftd.o :
	gcc -c ftd.c

dtf :
	gcc -o dtf.out main.c dtf.c fti.c dti.c itf.c dtf.c

