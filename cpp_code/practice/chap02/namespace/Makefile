app.out : main.o mike.o kitae.o
	g++ main.o mike.o kitae.o -o app.out
	rm -f *.o

main.o : main.cpp mike.h kitae.h
	g++ -c main.cpp -o main.o

mike.o : mike.cpp mike.h
	g++ -c mike.cpp -o mike.o

kitae.o : kitae.cpp kitae.h
	g++ -c kitae.cpp -o kitae.o


clean : 
	rm -rf *.o app.out

