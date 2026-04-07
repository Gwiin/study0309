app.out : main.o a.o b.o
	gcc main.o a.o b.o -o app.out

main.o : a.o b.o
	gcc -c main.c -o main.o

a.o :
	gcc -c a.c -o a.o

b.o :
	gcc -c b.c -o b.o

clean :
	rm -f *.o app.out